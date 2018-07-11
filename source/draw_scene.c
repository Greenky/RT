/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 20:57:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:58:59 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

int		draw_scene(t_rt *rt_data)
{
	t_dot	pixel;

	pixel.y = 0;
	while (pixel.y < SCR_SIZE)
	{
		pixel.x = 0;
		while (pixel.x < SCR_SIZE)
		{
			draw_pixel(rt_data, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
	return (0);
}

void	draw_pixel(t_rt *rt_data, t_dot pixel)
{
	t_ray		primary_ray;
	uint32_t	color;
	t_intersect	closest_inter;

	primary_ray = compute_ray(rt_data->camera, pixel);
	closest_inter = find_closest_inter(rt_data, primary_ray);
	if (closest_inter.distance == INFINITY)
		color = 0;
	else
//		color = 0xFFFFFF;
		color = find_color(rt_data, closest_inter, primary_ray);
	set_pixel(rt_data->screen_surface, pixel.x, pixel.y, color);
}
