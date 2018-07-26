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
	rt_data.filter = NOFILTER;
	rt_data.gui.filter_gui = 0;
	init_bar_positions(&rt_data);
	run_rt(&rt_data);
	return (0);
}
