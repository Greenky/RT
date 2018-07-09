/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 16:10:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 13:26:52 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int		main(int argc, char **argv)
{
	t_scene_data	scene;
	int				fd;

	if (argc != 2)
	{
		ft_putendl("usage: ./RTv1 scenes/scene_number");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (!check_argument(fd))
		return (0);
	if (read_file(&scene, fd) == FALSE)
	{
		ft_putendl("Error file");
		return (0);
	}
	run_rtv1(&scene);
	close(fd);
	return (0);
}
