/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 20:08:17 by vmazurok          #+#    #+#             */
/*   Updated: 2018/05/23 20:08:19 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_data.h"

int			key_hooks(int key, t_rt *rt_data)
{
	if (key == UP_ARROW)
		rt_data->camera.origin.z += 100;
	else if (key == DOWN_ARROW)
		rt_data->camera.origin.z -= 100;
	else if (key == PLUS)
		(rt_data->max_reflections)++;
	else if (key == MINUS)
		rt_data->max_reflections = fmax(0, rt_data->max_reflections - 1);
	// if (key == 27)
	// 	(rt_data->camera).dest -= 100;
	// else if (key == 24)
	// 	rt_data->camera.dest += 100;
	// else if (key == 123)
	// 	rt_data->camera.origin.x -= 100;
	// else if (key == 124)
	// 	rt_data->camera.origin.x += 100;
	// else if (key == 126)
	// 	rt_data->camera.direct.x -= 0.1;
	// else if (key == 125)
	// 	rt_data->camera.direct.x += 0.1;
	else if (key == ESC)
	{
		freesher(rt_data->light, rt_data->shapes);
		free(rt_data);
		exit(0);
	}
	ray_casting(rt_data);
	return (0);
}
