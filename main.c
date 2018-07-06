/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 20:08:17 by vmazurok          #+#    #+#             */
/*   Updated: 2018/05/23 20:08:19 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void		gfx_init(t_grafx *gfx)
{
	gfx->max_reflections = 1;
	if (!(gfx->mlx = mlx_init()))
	{
		freesher(gfx->light, gfx->shapes);
		free(gfx);
		perror("RTv1");
		exit(1);
	}
	if (!(gfx->win = mlx_new_window(gfx->mlx, SCR_SIZE, SCR_SIZE, "RTv1")))
	{
		freesher(gfx->light, gfx->shapes);
		free(gfx);
		perror("RTv1");
		exit(1);
	}
	if (!(gfx->img = mlx_new_image(gfx->mlx, SCR_SIZE, SCR_SIZE)))
	{
		freesher(gfx->light, gfx->shapes);
		free(gfx);
		perror("RTv1");
		exit(1);
	}
}

int			key_hooks(int key, t_grafx *gfx)
{
	if (key == UP_ARROW)
		gfx->camera.origin.z += 100;
	else if (key == DOWN_ARROW)
		gfx->camera.origin.z -= 100;
	else if (key == PLUS)
		(gfx->max_reflections)++;
	else if (key == MINUS)
		gfx->max_reflections = fmax(0, gfx->max_reflections - 1);
	// if (key == 27)
	// 	(gfx->camera).dest -= 100;
	// else if (key == 24)
	// 	gfx->camera.dest += 100;
	// else if (key == 123)
	// 	gfx->camera.origin.x -= 100;
	// else if (key == 124)
	// 	gfx->camera.origin.x += 100;
	// else if (key == 126)
	// 	gfx->camera.direct.x -= 0.1;
	// else if (key == 125)
	// 	gfx->camera.direct.x += 0.1;
	else if (key == ESC)
	{
		freesher(gfx->light, gfx->shapes);
		free(gfx);
		exit(0);
	}
	ray_casting(gfx);
	return (0);
}

int			main(int argc, char **argv)
{
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
	file_parcing(fd, gfx);
	gfx_init(gfx);
	ray_casting(gfx);
	mlx_key_hook(gfx->win, key_hooks, gfx);
	mlx_loop(gfx->mlx);
	return (0);
}
