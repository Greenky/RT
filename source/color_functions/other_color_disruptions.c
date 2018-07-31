/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_color_disruptions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 22:29:14 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/31 20:23:18 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

uint32_t	rgb_to_int(t_channel rgb)
{
	int c;

	c = rgb.red;
	c = (c << 8) | rgb.green;
	c = (c << 8) | rgb.blue;
	return ((uint32_t)c);
}

int			check_mate_disruption(int j, int i)
{
	if ((j % 50 < 25 && i % 50 < 25) || (j % 50 > 25 && i % 50 > 25))
		return (j < 0 ? 0 : 0xFFFFFF);
	else
		return (j < 0 ? 0xFFFFFF : 0);
}

int			plasma_disruption(int j, int i)
{
	int			color;
	double		time;
	double		value;

	time = clock() / 50.0;
	value = sin(dist(i + time, j, 100 / 2,
							100 / 2) / 8.0)
						+ sin(dist(i, j, 100 / 4, 100 / 4) / 8.0)
						+ sin(dist(i, j + time / 7, (100 / 4 * 3),
								100 / 4) / 7.0)
						+ sin(dist(i, j, (100 / 4 * 3), 100.0) / 8.0);
	color = (int)((4 + value)) * 32;
	return (rgb_to_int((t_channel){color, color * 2, 255 - color}));
}
