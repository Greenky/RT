/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_color_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 21:20:44 by ikachko           #+#    #+#             */
/*   Updated: 2018/08/02 17:24:46 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

t_channel	fig_color_with_light(t_channel light_coef,
			t_intersect closest_inter)
{
	t_channel	color;

	color.red = fig_color_with_light_channel(
			closest_inter.texture_color.red, light_coef.red + (40 * closest_inter.fig->is_cartoon));
	color.green = fig_color_with_light_channel(
			closest_inter.texture_color.green, light_coef.green + (40 * closest_inter.fig->is_cartoon));
	color.blue = fig_color_with_light_channel(
			closest_inter.texture_color.blue, light_coef.blue + (40 * closest_inter.fig->is_cartoon));
	return (color);
}

uint32_t	fig_color_with_light_channel(float fig_color, float light_color)
{
	uint32_t	new_color;

	if (fig_color < 0 || light_color < 0)
		return (0);
	new_color = (uint32_t)(fig_color * light_color) >> 8;
	if (new_color > 0xFF)
		new_color = 0xFF;
	return (new_color);
}

t_channel	color_plus_color(t_channel color1, t_channel color2)
{
	color1.red += color2.red;
	color1.green += color2.green;
	color1.blue += color2.blue;
	return (color1);
}

uint32_t	channel_color_to_uint(t_channel color)
{
	uint32_t	color_hex;

	color_hex = (uint32_t)color.red << 16;
	color_hex += (uint32_t)color.green << 8;
	color_hex += (uint32_t)color.blue;
	return (color_hex);
}
