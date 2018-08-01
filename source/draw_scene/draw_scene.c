/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:26:43 by vmazurok          #+#    #+#             */
/*   Updated: 2018/08/01 20:32:53 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int			draw_scene(t_rt *scene)
{
	pthread_t		threads[THREAD_MAX];
	t_thread_data	thread_num[THREAD_MAX];
	int				idx;

	set_tread_param(scene, thread_num);
	idx = 0;
	while (idx < THREAD_MAX)
	{
		pthread_create(&threads[idx], NULL,
		(scene->filter == PIXEL) ? draw_pixel_strings : draw_strings,
		(thread_num + idx));
		idx++;
	}
	idx = 0;
	while (idx < THREAD_MAX)
		pthread_join(threads[idx++], NULL);
	if (scene->take_screenshot == 0)
	{
		draw_clicked_info(scene);
		draw_gui(scene);
	}
	return (0);
}

void		set_tread_param(t_rt *scene, t_thread_data *thread_num)
{
	int		idx;

	idx = 0;
	while (idx < THREAD_MAX)
	{
		thread_num[idx].scene = scene;
		thread_num[idx].string_num = idx;
		idx++;
	}
}

void		*draw_strings(void *thread_data_void)
{
	t_dot			pixel;
	t_thread_data	*thread_data;

	thread_data = (t_thread_data*)thread_data_void;
	pixel.y = thread_data->string_num * thread_data->scene->aliasing;
	while (pixel.y < WIN_SIZE * thread_data->scene->aliasing)
	{
		pixel.x = 0;
		while (pixel.x < WIN_SIZE * thread_data->scene->aliasing)
		{
			draw_pixel_with_aa(thread_data->scene, pixel);
			pixel.x += thread_data->scene->aliasing;
		}
		pixel.y += THREAD_MAX * thread_data->scene->aliasing;
	}
	return (NULL);
}

void		draw_pixel_with_aa(t_rt *rt_data, t_dot pixel)
{
	uint32_t	color_hex;
	t_channel	color;
	t_dot		new_pixel;

	new_pixel = pixel;
	color = (t_channel){0, 0, 0};
	while (new_pixel.y < pixel.y + rt_data->aliasing)
	{
		new_pixel.x = pixel.x;
		while (new_pixel.x < pixel.x + rt_data->aliasing)
		{
			color = color_plus_color(color,
			get_pixel_color(rt_data, new_pixel));
			new_pixel.x++;
		}
		new_pixel.y++;
	}
	color.red /= find_square(rt_data->aliasing);
	color.green /= find_square(rt_data->aliasing);
	color.blue /= find_square(rt_data->aliasing);
	color_hex = channel_color_to_uint(color);
	if (rt_data->filter != -1)
		color_hex = apply_filter(color_hex, rt_data->filter);
	set_pixel(rt_data->screen_surface, pixel.x / rt_data->aliasing,
	pixel.y / rt_data->aliasing, color_hex);
}

t_channel	get_pixel_color(t_rt *rt_data, t_dot pixel)
{
	t_ray		primary_ray;
	t_channel	color;
	t_intersect	closest_inter;

	primary_ray = compute_ray(rt_data->cl_data.camera, pixel,
	rt_data->aliasing);
	closest_inter = find_closest_inter(rt_data->cl_data,
						rt_data->objects_arr, primary_ray);
	if (closest_inter.distance == INFINITY)
		color = (t_channel) {0, 0, 0};
	else
		color = find_color(rt_data,
						rt_data->cl_data, closest_inter, primary_ray);
	return (color);
}
