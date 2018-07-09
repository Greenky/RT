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

#include "rt_functions.h"

void		rt_data_graphic_init(t_rt *rt_data)
{
	rt_data->max_reflections = 8;
	// if (!(rt_data->mlx = mlx_init()))
	// {
	// 	freesher(rt_data->light, rt_data->shapes);
	// 	perror("RT");
	// 	exit(1);
	// }
	// if (!(rt_data->win = mlx_new_window(rt_data->mlx, SCR_SIZE, SCR_SIZE, "RT")))
	// {
	// 	freesher(rt_data->light, rt_data->shapes);
	// 	perror("RT");
	// 	exit(1);
	// }
	// if (!(rt_data->img = mlx_new_image(rt_data->mlx, SCR_SIZE, SCR_SIZE)))
	// {
	// 	freesher(rt_data->light, rt_data->shapes);
	// 	perror("RT");
	// 	exit(1);
	// }
	SDL_Init(SDL_INIT_EVERYTHING);
	rt_data->window = SDL_CreateWindow("SDL window", SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, 1000,
								1000, SDL_WINDOW_ALLOW_HIGHDPI);
	rt_data->surface = SDL_GetWindowSurface(rt_data->window);
}

/*
** rt_data - RT Data
** 
*/

void		check_number_of_params(int argc)
{
	if (argc != 2)
	{
		write(2, "Input must include one parameter\n", 33);
		write(2, "Usage: ./RT scenes/[scene]\n", 27);
		exit(1);
	}
}

int			main(int argc, char **argv)
{
	t_rt	rt_data;
	int		fd;

	check_number_of_params(argc);
	if (((fd = open(argv[1], O_RDONLY)) < 0) || (read(fd, NULL, 0) < 0))
	{
		perror("RT");
		exit(1);
	}
	file_parcing(fd, &rt_data);
	printf("file parsed\n");
	rt_data_graphic_init(&rt_data);
	printf("file parsed1\n");
	// while (rt_data.shapes)
	// {
	// 	printf("name - %c, id - %i\n", rt_data.shapes->name, rt_data.shapes->id);
	// 	rt_data.shapes = rt_data.shapes->next;
	// }
	while (1)
		ray_casting(&rt_data);
	// mlx_key_hook(rt_data.win, key_hooks, &rt_data);
	// mlx_loop(rt_data.mlx);
	return (0);
}
