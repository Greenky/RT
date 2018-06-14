/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 20:08:17 by vmazurok          #+#    #+#             */
/*   Updated: 2018/05/23 20:08:19 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static void	cam_fill(char **line, t_camera *camera, int l_num, int *flag)
{
	char *new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "dir:"))
	{
		*line = trim_from(*line, 4);
		(*camera).direct = v_to_len(parce_vector(*line, l_num), 1, 0);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		(*camera).origin = parce_vector(*line, l_num);
		*flag = *flag | 2;
	}
	else
		error_caster(l_num, "no such parameter as ", *line);
}

int			cam_parce(int fd, int *l_num, t_camera *camera)
{
	int			k;
	int			flag;
	char		*line;

	flag = 0;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(*l_num)++;
		cam_fill(&line, camera, *l_num, &flag);
		ft_strdel(&line);
		if (flag == 3)
			break ;
	}
	if (k < 0)
	{
		perror("RTv1");
		exit(1);
	}
	(*camera).is_set = 1;
	return (0);
}

void		gfx_init(t_grafx *gfx, t_shape **shape_list, t_light **light)
{
	if (!(gfx->mlx = mlx_init()))
	{
		freesher(light, shape_list);
		free(gfx);
		perror("RTv1");
		exit(1);
	}
	if (!(gfx->win = mlx_new_window(gfx->mlx, SCR_SIZE, SCR_SIZE, "RTv1")))
	{
		freesher(light, shape_list);
		free(gfx);
		perror("RTv1");
		exit(1);
	}
	if (!(gfx->img = mlx_new_image(gfx->mlx, SCR_SIZE, SCR_SIZE)))
	{
		freesher(light, shape_list);
		free(gfx);
		perror("RTv1");
		exit(1);
	}
}

int			exit_func(int key, t_grafx *gfx)
{
	if (key == 27)
		(*(gfx->camera)).dest -= 100;
	else if (key == 24)
		(*(gfx->camera)).dest += 100;
	else if (key == 123)
		(*(gfx->camera)).origin.x -= 100;
	else if (key == 124)
		(*(gfx->camera)).origin.x += 100;
	else if (key == 126)
		(*(gfx->camera)).direct.x -= 0.1;
	else if (key == 125)
		(*(gfx->camera)).direct.x += 0.1;
	if (key == ESC)
	{
		freesher(gfx->light, gfx->shapes);
		free(gfx);
		exit(0);
	}
	ray_casting(gfx, *(gfx->shapes), *(gfx->light), *(gfx->camera));
	return (0);
}

int			main(int argc, char **argv)
{
	t_shape		*shape_list;
	t_camera	camera;
	t_light		*light;
	t_grafx		*gfx;
	int			fd;

	if (argc != 2 && write(2, "Input must include one parameter\n", 33))
		exit(1);
	if (((fd = open(argv[1], O_RDONLY)) < 0) || (read(fd, NULL, 0) < 0))
	{
		perror("RTv1");
		exit(1);
	}
	gfx = (t_grafx *)malloc(sizeof(t_grafx));
	gfx->shapes = &shape_list;
	gfx->light = &light;
	gfx->camera = &camera;
	file_parcing(fd, gfx);
	gfx_init(gfx, &shape_list, &light);
	ray_casting(gfx, shape_list, light, camera);
	mlx_key_hook(gfx->win, exit_func, gfx);
	mlx_loop(gfx->mlx);
	return (0);
}
