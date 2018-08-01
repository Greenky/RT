/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_filter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 15:28:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/31 20:56:37 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void		*draw_pixel_strings(void *thread_data_void)
{
	t_dot			pixel;
	t_thread_data	*thread_data;

	thread_data = (t_thread_data*)thread_data_void;
	pixel.y = thread_data->string_num * PIXEL_SIZE;
	while (pixel.y < WIN_SIZE)
	{
		pixel.x = 0;
		while (pixel.x < WIN_SIZE)
		{
			draw_pixel_pixel(thread_data->scene, pixel);
			pixel.x += PIXEL_SIZE;
		}
		pixel.y += THREAD_MAX * PIXEL_SIZE;
	}
	return (NULL);
}

void		draw_pixel_pixel(t_rt *rt_data, t_dot pixel)
{
	t_ray			primary_ray;
	uint32_t		color_hex;
	t_intersect		closest_inter;
	t_dot			new_pixel;

	primary_ray = compute_ray(rt_data->cl_data.camera, pixel, 1);
	closest_inter = find_closest_inter(rt_data->cl_data,
									rt_data->objects_arr, primary_ray);
	if (closest_inter.distance == INFINITY)
		color_hex = 0;
	else
		color_hex = channel_color_to_uint(find_color(rt_data,
						rt_data->cl_data, closest_inter, primary_ray));
	new_pixel.y = pixel.y - 1;
	while (++new_pixel.y < pixel.y + PIXEL_SIZE && new_pixel.y < WIN_SIZE)
	{
		new_pixel.x = pixel.x - 1;
		while (++new_pixel.x < pixel.x + PIXEL_SIZE && new_pixel.x < WIN_SIZE)
			set_pixel(rt_data->screen_surface,
			new_pixel.x, new_pixel.y, color_hex);
	}
}
