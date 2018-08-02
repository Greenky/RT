/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parcing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:14:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/01 15:20:49 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void		file_parcing(char *file, t_rt *rt_data)
{
	const t_parce	arr[] = {
					{"camera:", &cam_parce},
					{"light:", &light_parce},
					{"sphere:", &sphere_parce},
					{"plane:", &plane_parce},
					{"cone:", &cone_parce},
					{"cylinder:", &cylinder_parce},
					{"ellipsoid:", &ellipsoid_parce},
					{"triangle:", &triangle_parce}
			};
	int				fd;

	fd = find_fd(file);
	rt_data->objects = NULL;
	rt_data->lights = NULL;
	rt_data->cl_data.reflect_rate = 0;
	rt_data->cl_data.camera.is_set = 0;
	rt_data->cl_data.trancparent_rate = 0;
	rt_data->cl_data.max_reflections = 5;
	rt_data->cl_data.max_trancparent = 5;
	line_reader(rt_data, fd, arr);
	if (!rt_data->cl_data.camera.is_set)
		error_exit(CAM_ERROR, rt_data);
	correct_plane_normal(rt_data);
	init_arrays(rt_data);
}

void		line_reader(t_rt *rt_data, int fd, const t_parce arr[])
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

void		parcer_functions(char **str,
							t_rt *rt_data, const t_parce arr[], int fd)
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
			if (vect_scalar_mult(object_list->normal,
								rt_data->cl_data.camera.basis.b_z) <= 0)
				object_list->normal =
						vect_mult_scalar(object_list->normal, -1);
		}
		object_list = object_list->next;
	}
}
