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

/*uint32_t	find_color_hex(t_channel light_coef, t_intersect closest_inter)
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
}*/

t_channel	fig_color_with_light(t_channel light_coef, t_intersect closest_inter)
{
	t_channel	color;

	color.red = fig_color_with_light_channel(closest_inter.texture_color.red,
											light_coef.red);
	color.green = fig_color_with_light_channel(closest_inter.texture_color.green,
											light_coef.green);
	color.blue = fig_color_with_light_channel(closest_inter.texture_color.blue,
											light_coef.blue);
	return (color);
}

/*uint32_t	find_color_channel(float fig_color_channel,
					float light_color_channel, int step)
{
	uint32_t	mult;

	if (fig_color_channel < 0 || light_color_channel < 0)
		return (0);
	mult = (uint32_t)(fig_color_channel * light_color_channel) >> 8;
	if (mult > 0xFF)
		mult = 0xFF;
	return (mult << step);
}*/

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
