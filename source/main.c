/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 20:08:17 by vmazurok          #+#    #+#             */
/*   Updated: 2018/07/31 21:17:47 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

int			main(int argc, char **argv)
{
	t_rt	rt_data;

	if (argc < 2)
		error_exit(NUM_OF_ARG, NULL);
	file_parcing(argv[1], &rt_data);
	init_gui_bmps(&rt_data);
	init_foot_gui_bmps(&rt_data);
	rt_data.aliasing = 0;
	if (argc == 3 && ft_strequ(argv[2], "-s"))
	{
		init_server(&rt_data, argv[1]);
		rt_data.server_mode = 1;
	}
	else
		rt_data.server_mode = 0;
	rt_data.is_client = 0;
	rt_data.filter = NOFILTER;
	rt_data.gui.filter_gui = 0;
	init_bar_positions(&rt_data);
	run_rt(&rt_data);
	return (0);
}
