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

#include "rt_data.h"

void		rt_data_graphic_init(t_rt *rt_data)
{
	rt_data->max_reflections = 8;
	if (!(rt_data->mlx = mlx_init()))
	{
		freesher(rt_data->light, rt_data->shapes);
		free(rt_data);
		perror("RT");
		exit(1);
	}
	if (!(rt_data->win = mlx_new_window(rt_data->mlx, SCR_SIZE, SCR_SIZE, "RT")))
	{
		freesher(rt_data->light, rt_data->shapes);
		free(rt_data);
		perror("RT");
		exit(1);
	}
	if (!(rt_data->img = mlx_new_image(rt_data->mlx, SCR_SIZE, SCR_SIZE)))
	{
		freesher(rt_data->light, rt_data->shapes);
		free(rt_data);
		perror("RT");
		exit(1);
	}
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
		write(2, "Usage: ./RT scenes/[scene]\n", 20);
		exit(1);
	}
}

int			main(int argc, char **argv)
{
	t_rt	*rt_data;
	int		fd;

	check_number_of_params(argc);
	if (((fd = open(argv[1], O_RDONLY)) < 0) || (read(fd, NULL, 0) < 0))
	{
		perror("RT");
		exit(1);
	}
	file_parcing(fd, &rt_data);
	rt_data_graphic_init(&rt_data);
	ray_casting(&rt_data);
	mlx_key_hook(rt_data.win, key_hooks, &rt_data);
	mlx_loop(rt_data.mlx);
	return (0);
}
