/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_color_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 21:20:44 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/25 21:20:46 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

uint32_t	find_color_hex(t_channel light_coef, t_intersect closest_inter)
{
	uint32_t	color_hex;

	color_hex = 0;
	color_hex += find_color_channel(closest_inter.texture_color.red,
									light_coef.red, 16);
	color_hex += find_color_channel(closest_inter.texture_color.green,
									light_coef.green, 8);
	color_hex += find_color_channel(closest_inter.texture_color.blue,
									light_coef.blue, 0);
	return (color_hex);
}

uint32_t	find_color_channel(float fig_color_channel,
					float light_color_channel, int step)
{
	uint32_t	mult;

	if (fig_color_channel < 0 || light_color_channel < 0)
		return (0);
	mult = (uint32_t)(fig_color_channel * light_color_channel) >> 8;
	if (mult > 0xFF)
		mult = 0xFF;
	return (mult << step);
}
