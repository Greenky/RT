/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parcing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:45:56 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/05 16:45:57 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_data.h"

static void		parcer_functions(char **str, t_rt *rt_data, const t_parce arr[],
int fd)
{
	static int	id;
	int			i;

	i = 0;
	while (i < OBJ_NUM)
	{
		if (**str == 0 || **str == '#')
			break ;
		else if (ft_strequ(*str, arr[i].name))
		{
			arr[i].parce(fd, rt_data, id++);
			break ;
		}
		i++;
		if (i == OBJ_NUM)
		{
			freesher(rt_data->light, rt_data->shapes);
			error_caster(rt_data->line_number, "no such object as ", *str);
		}
	}
}

static void		line_reader(t_rt *rt_data, int fd, const t_parce arr[])
{
	int			k;
	char		*line;
	char		*buffer_line;

	rt_data->line_number = 0;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		buffer_line = ft_strtrim(line);
		free(line);
		line = buffer_line;
		parcer_functions(&line, rt_data, arr, fd);
		ft_strdel(&line);
	}
	if (k < 0)
	{
		freesher(rt_data->light, rt_data->shapes);
		perror("RTv1");
		exit(1);
	}
}

static t_camera	cam_config(t_camera camera)
{
	camera.dest = SCR_SIZE * cos(M_PI / 6);
	camera.direct = v_to_len(camera.direct, 1, 0);
	if (camera.direct.x == 0 && camera.direct.z == 0)
	{
		camera.up = set_vector(1, 0, 0);
		camera.right = set_vector(0, 1, 0);
	}
	else
	{
		camera.up = set_vector(0, -1, 0);
		camera.right = vec_dob(camera.direct, camera.up);
		camera.right = v_to_len(camera.right, 1, 0);
		camera.up = vec_dob(camera.right, camera.direct);
	}
	return (camera);
}

static void		correct_plane_normal(t_rt *rt_data)
{
	t_vector nor;
	t_shape *shape_list;

	shape_list = rt_data->shapes;
	while (shape_list)
	{
		if (shape_list->name == 'p')
		{
			nor = ((t_plane *)(shape_list->shape))->normal;
			if (scalar_dob(nor, rt_data->camera.direct) <= 0)
				((t_plane *)(shape_list->shape))->normal =
			v_to_len(nor, -1, 0);
		}
		shape_list = shape_list->next;
	}
}

void			file_parcing(int fd, t_rt *rt_data)
{
	const t_parce arr[] =
	{
			{"camera:", &cam_parce},
			{"light:", &light_parce},
			{"sphere:", &sphere_parce},
			{"plane:", &plane_parce},
			{"cone:", &cone_parce},
			{"cylinder:", &cylin_parce}
	};

	rt_data->shapes = NULL;
	rt_data->light = NULL;
	rt_data->camera.is_set = 0;
	line_reader(rt_data, fd, arr);
	if (!rt_data->camera.is_set)
	{
		freesher(rt_data->light, rt_data->shapes);
		ft_putendl("You have no camera, ma dudes");
		system("say \"You have no camera, ma dudes\"");
		exit(1);
	}
	correct_plane_normal(rt_data);
	rt_data->camera = cam_config(rt_data->camera);
}
