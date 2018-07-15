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
//	argc = 1;
//	argv = NULL;
	t_rt	rt_data;
	if (argc != 2)
		error_exit(NUM_OF_ARG, NULL);
// 	Я хз як передавати параметри в Windows тому так. І потім це єдиний працюючий файл)
	file_parcing(argv[1], &rt_data);
	ray_tracing(&rt_data);
	return (0);
}
