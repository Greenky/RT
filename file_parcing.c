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

#include "gfx.h"

static void		parcer_functions(char **str, t_grafx *gfx, const t_parce arr[],
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
			if (ft_strequ(*str, "camera:"))
				cam_parce(fd, &(gfx->l_num), gfx->camera);
			else if (ft_strequ(*str, "light:"))
				arr[i].parce(fd, &(gfx->l_num), (void **)(gfx->light), 0);
			else
				arr[i].parce(fd, &(gfx->l_num), (void **)(gfx->shapes), id++);
			break ;
		}
		i++;
		if (i == OBJ_NUM)
		{
			freesher(gfx->light, gfx->shapes);
			error_caster(gfx->l_num, "no such object as ", *str);
		}
	}
}

static void		line_reader(t_grafx *gfx, int fd, const t_parce arr[])
{
	int			k;
	char		*line;
	char		*new_line;

	gfx->l_num = 0;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(gfx->l_num)++;
		new_line = ft_strtrim(line);
		free(line);
		line = new_line;
		parcer_functions(&line, gfx, arr, fd);
		ft_strdel(&line);
	}
	if (k < 0)
	{
		freesher(gfx->light, gfx->shapes);
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

static void		correct_plane_normal(t_shape *shape_list, t_camera camera)
{
	t_vector nor;

	while (shape_list)
	{
		if (shape_list->name == 'p')
		{
			nor = ((t_plane *)(shape_list->shape))->normal;
			if (scalar_dob(nor, camera.direct) <= 0)
				((t_plane *)(shape_list->shape))->normal =
			v_to_len(nor, -1, 0);
		}
		shape_list = shape_list->next;
	}
}

void			file_parcing(int fd, t_grafx *gfx)
{
	const t_parce arr[] = {{"camera:", NULL}, {"light:", &light_parce},
	{"sphere:", &sphere_parce}, {"plane:", &plane_parce},
	{"cone:", &cone_parce}, {"cylinder:", &cylin_parce}};

	*(gfx->shapes) = NULL;
	*(gfx->light) = NULL;
	(*(gfx->camera)).is_set = 0;
	line_reader(gfx, fd, arr);
	if (!(*(gfx->camera)).is_set)
	{
		freesher(gfx->light, gfx->shapes);
		ft_putendl("You have no camera, ma dudes");
		system("say \"You have no camera, ma dudes\"");
		exit(1);
	}
	correct_plane_normal(*(gfx->shapes), *(gfx->camera));
	*(gfx->camera) = cam_config(*(gfx->camera));
}
