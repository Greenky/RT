/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_filter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 15:28:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/28 15:28:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void		*draw_pixel_strings(void *thread_data_void)
{
	t_dot			pixel;
	t_thread_data	*thread_data;

	thread_data = (t_thread_data*)thread_data_void;
	pixel.y = thread_data->string_num;
	while (pixel.y < SCR_SIZE)
	{
		pixel.x = 0;
		while (pixel.x < SCR_SIZE)
		{
			draw_pixel_pixel(thread_data->scene, pixel);
			pixel.x += 10;
		}
		pixel.y += THREAD_MAX;
	}
	return (NULL);
}

void		draw_pixel_pixel(t_rt *rt_data, t_dot pixel)
{
	t_ray			primary_ray;
	t_channel		color;
	uint32_t		color_hex;
	t_intersect		closest_inter;

	primary_ray = compute_ray(rt_data->cl_data.camera, pixel, 1);
	closest_inter = find_closest_inter(rt_data->cl_data,
									rt_data->objects_arr, primary_ray);
	rt_data->cl_data.max_reflections = 5;
	rt_data->cl_data.reflect_rate = 0;
	if (closest_inter.distance == INFINITY)
		color = (t_channel){0, 0, 0};
	else
		color = find_color(rt_data,
						rt_data->cl_data, closest_inter, primary_ray);
	color_hex = channel_color_to_uint(color);
	if (rt_data->filter != -1)
		color_hex = apply_filter(color_hex, rt_data->filter);
	set_pixel(rt_data->screen_surface, pixel.x, pixel.y, color_hex);
	int	x = pixel.x - 1;//TODO fix
	int	y = pixel.y - 1;//TODO fix
	while(++y < pixel.y + 10 && y < SCR_SIZE)
		while (++x < pixel.x + 10 && x < SCR_SIZE)
			set_pixel(rt_data->screen_surface, x, y, color_hex);
}
