/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_color_disruptions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 22:29:14 by ikachko           #+#    #+#             */
/*   Updated: 2018/08/02 11:00:32 by ikachko          ###   ########.fr       */
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
	j = j < 0 ? -j : j;
	i = i < 0 ? -i : i;
	if ((j % 50 < 25 && i % 50 < 25) || (j % 50 > 25 && i % 50 > 25))
		return (j < 0 ? 0 : 0xFFFFFF);
	else
		return (j < 0 ? 0xFFFFFF : 0);
}

int			plasma_disruption(int j, int i)
{
	int			color;

	color = (int)(128.0 * sin(j / 16.0)
				+ 128.0 + (128.0 * sin(i / 16.0))) / 2;
	return (color);
}
