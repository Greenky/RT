/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 15:21:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/31 20:55:17 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

uint32_t	apply_filter(uint32_t color, int filter)
{
	t_channel	clr;
	t_channel	tmp;

	if (filter == NEGATIVE)
		return (0xFFFFFF - color);
	clr = int_to_channels(color);
	if (filter == GREYSCALE)
	{
		color = (uint32_t)(clr.red * 0.299 + clr.green * 0.587
						+ clr.blue * 0.114);
		return (color << 16 | color << 8 | color);
	}
	if (filter == SEPIA)
	{
		tmp = (t_channel){(uint32_t)(0.393 * clr.red + 0.769 * clr.green
		+ 0.189 * clr.blue), (uint32_t)(0.349 * clr.red + 0.686 * clr.green
		+ 0.168 * clr.blue), (uint32_t)(0.272 * clr.red + 0.534 * clr.green
		+ 0.131 * clr.blue)};
		clr = (t_channel){(uint32_t)((tmp.red > 255) ? 255 : tmp.red),
						(uint32_t)((tmp.green > 255) ? 255 : tmp.green),
						(uint32_t)((tmp.blue > 255) ? 255 : tmp.blue)};
		return ((uint32_t)clr.red << 16
				| (uint32_t)clr.green << 8 | (uint32_t)clr.blue);
	}
	return (color);
}
