/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parcing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:14:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/07 12:14:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

// New functions --------------------------------------------------

void			init_arrays(t_rt *rt_data) //TODO розбити по функціям
{
	t_objects *step_obj;
	t_light *step_light;
	int len;

	len = 0;
	step_obj = rt_data->objects;
	while (step_obj)
	{
		len++;
		step_obj = step_obj->next;
	}
	rt_data->cl_data.num_of_objects = len;
	rt_data->objects_arr = (t_objects *)malloc(sizeof(t_objects) * len);
	len = 0;
	step_obj = rt_data->objects;
	while (len < rt_data->cl_data.num_of_objects)
	{
		rt_data->objects_arr[len].type = step_obj->type;
		rt_data->objects_arr[len].color = step_obj->color;
		rt_data->objects_arr[len].origin = step_obj->origin;
		rt_data->objects_arr[len].normal = step_obj->normal;
		rt_data->objects_arr[len].radius = step_obj->radius;
		rt_data->objects_arr[len].angle_coef = step_obj->angle_coef;
		rt_data->objects_arr[len].basis = step_obj->basis;
		rt_data->objects_arr[len].mirror_coef = step_obj->mirror_coef;
		rt_data->objects_arr[len].axis_dimensions = step_obj->axis_dimensions;
		rt_data->objects_arr[len].bling_phong = step_obj->bling_phong;
		rt_data->objects_arr[len].mirror_coef = step_obj->mirror_coef;

		// KOSTIL ----------------------------------------------------------------- // TODO udolit

		// Transperency ------------------------
		rt_data->objects_arr[len].transperent_coef = (step_obj->type == SPHERE ? 1 : 0);

		// Textures ---------------------
		if (step_obj->type == SPHERE)
			rt_data->objects_arr[len].texture_index = -1;
		else if (step_obj->type == CYLINDER)
			rt_data->objects_arr[len].texture_index = -1;
		else if (step_obj->type == CONE)
			rt_data->objects_arr[len].texture_index = 2;
		else
			rt_data->objects_arr[len].texture_index = 1;
		// ------------------------------------------------------------------------
		rt_data->objects_arr[len].is_cartoon = 0;
		rt_data->objects_arr[len].next = NULL;
		len++;
		step_obj = step_obj->next;
	}
	len = 0;
	step_light = rt_data->lights;
	while (step_light)
	{
		len++;
		step_light = step_light->next;
	}
//	rt_data->lights_num = len;
	rt_data->cl_data.num_of_lights = len;
	rt_data->lights_arr = (t_light *)malloc(sizeof(t_light) * len);
	len = 0;
	step_light = rt_data->lights;
	while (len < rt_data->cl_data.num_of_lights)
	{
		rt_data->lights_arr[len].origin = step_light->origin;
		rt_data->lights_arr[len].color = step_light->color;
		rt_data->lights_arr[len].type = step_light->type;
		rt_data->lights_arr[len].direct = step_light->direct;
		rt_data->lights_arr[len].intensity = step_light->intensity;
		rt_data->lights_arr[len].next = NULL;
		len++;
		step_light = step_light->next;
	}
//	freesher(rt_data->lights, rt_data->objects);
//	rt_data->lights = NULL;
//	rt_data->objects = NULL;
}

//--------------------------------------------------------------------------

void			file_parcing(char *file, t_rt *rt_data)
{
	const t_parce arr[] =
			{
					{"camera:", &cam_parce},
					{"light:", &light_parce},
					{"sphere:", &sphere_parce},
					{"plane:", &plane_parce},
					{"cone:", &cone_parce},
					{"cylinder:", &cylinder_parce}
			};
	int		fd;

	fd = find_fd(file);
	rt_data->objects = NULL;
	rt_data->lights = NULL;
	rt_data->cl_data.camera.is_set = 0; // new
	rt_data->cl_data.max_reflections = 5;
	line_reader(rt_data, fd, arr);
	if (!rt_data->cl_data.camera.is_set)
		error_exit(CAM_ERROR, rt_data);
	init_arrays(rt_data);
	correct_plane_normal(rt_data);
}

void    		line_reader(t_rt *rt_data, int fd, const t_parce arr[])
{
	int			ret;
	char		*line;
	char		*new_line;

	rt_data->line_number = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		new_line = ft_strtrim(line);
		free(line);
		line = new_line;
		parcer_functions(&line, rt_data, arr, fd);
		ft_strdel(&line);
	}
	if (ret < 0)
		error_exit(ERROR, rt_data);
}

void		parcer_functions(char **str, t_rt *rt_data, const t_parce arr[], int fd)
{
	int		i;

	i = 0;
	while (i < OBJ_NUM)
	{
		if (**str == 0 || **str == '#' || **str == '$')
			break ;
		else if (ft_strequ(*str, arr[i].name))
		{
			arr[i].parce(fd, rt_data);
			break ;
		}
		i++;
		if (i == OBJ_NUM)
		{
			freesher(rt_data->lights, rt_data->objects);
			error_caster(rt_data->line_number, "no such object as ", *str);
		}
	}
}

void		correct_plane_normal(t_rt *rt_data)
{
    t_objects	*object_list;

	object_list = rt_data->objects;
	while (object_list)
	{
		if (object_list->type == PLANE)
		{
			if (vect_scalar_mult(object_list->normal, rt_data->cl_data.camera.basis.b_z) <= 0)
				object_list->normal = vect_mult_scalar(object_list->normal, -1);
		}
		object_list = object_list->next;
	}
}
//-------------------------------------------------- TODO перенести
t_coord_sys	create_coord_system(t_coord_sys basis)
{
	basis.b_z = normalize_vector(basis.b_z);
	if (basis.b_z.x == 0 && basis.b_z.z == 0)
	{
		basis.b_y = VEC(1, 0, 0);
		basis.b_x = VEC(0, 0, 1);
	}
	else
	{
		basis.b_y = VEC(0, -1, 0);
		basis.b_x = vect_cross_product(basis.b_z, basis.b_y);
		basis.b_x = normalize_vector(basis.b_x);
		basis.b_y = vect_cross_product(basis.b_x, basis.b_z);
		basis.b_x = vect_mult_scalar(basis.b_x, -1); // TODO костиль для правильного керування - пофіксити
	}
	return (basis);
}
