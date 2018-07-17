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

#include "../../includes/rt_functions.h"

//* THREADS  for debug ----------------------------------------------

#include <pthread.h>
# define THREAD_MAX 4

typedef struct		s_thread_data
{
	t_rt			*rt_data;
	int				string_num;
}					t_thread_data;

void	*draw_strings(void *thread_data_void);
void	set_tread_param(t_rt *rt_data, t_thread_data *thread_num);

int		draw_scene(t_rt *rt_data)
{
	pthread_t		threads[THREAD_MAX];
	t_thread_data	thread_num[THREAD_MAX];
	int				idx;

	set_tread_param(rt_data, thread_num);
	idx = 0;
	while (idx < THREAD_MAX)
	{
		pthread_create(&threads[idx], NULL, draw_strings,
						(thread_num + idx));
		idx++;
	}
	idx = 0;
	while (idx < THREAD_MAX)
		pthread_join(threads[idx++], NULL);
	return (0);
}

void	*draw_strings(void *thread_data_void)
{
	t_dot			pixel;
	t_thread_data	*thread_data;

	thread_data = (t_thread_data*)thread_data_void;
	pixel.y = thread_data->string_num * ANTI_ALIASING;
	while (pixel.y < WIN_SIZE * ANTI_ALIASING)
	{
		pixel.x = 0;
		while (pixel.x < WIN_SIZE * ANTI_ALIASING)
		{
			draw_pixel_with_aa(thread_data->rt_data, pixel);
			pixel.x += ANTI_ALIASING;
		}
		pixel.y += THREAD_MAX * ANTI_ALIASING;
	}
	return (NULL);
}

void	set_tread_param(t_rt *rt_data, t_thread_data *thread_num)
{
	int		idx;

	idx = 0;
	while (idx < THREAD_MAX)
	{
		thread_num[idx].rt_data = rt_data;
		thread_num[idx].string_num = idx;
		idx++;
	}
}

t_channel	color_plus_color(t_channel color1, t_channel color2)
{
	color1.red += color2.red;
	color1.green += color2.green;
	color1.blue += color2.blue;
	return (color1);
}

void	draw_pixel_with_aa(t_rt *rt_data, t_dot pixel)
{
	uint32_t	color_hex;
	t_channel	color;
	t_dot		new_pixel;

	new_pixel = pixel;
	color = (t_channel){0, 0, 0};
	while (new_pixel.y < pixel.y + ANTI_ALIASING)
	{
		new_pixel.x = pixel.x;
		while (new_pixel.x < pixel.x + ANTI_ALIASING)
		{
			color = color_plus_color(color, get_pixel_color(rt_data, new_pixel));
			new_pixel.x++;
		}
		new_pixel.y++;
	}
	color.red /= find_square(ANTI_ALIASING);
	color.green /= find_square(ANTI_ALIASING);
	color.blue /= find_square(ANTI_ALIASING);
	color_hex = channel_color_to_uint(color);
	set_pixel(rt_data->screen_surface, pixel.x / ANTI_ALIASING, pixel.y / ANTI_ALIASING, color_hex);
}

uint32_t	channel_color_to_uint(t_channel color)
{
	uint32_t	color_hex;

	color_hex = (uint32_t)color.red << 16;
	color_hex += (uint32_t)color.green << 8;
	color_hex += (uint32_t)color.blue;
	return (color_hex);
}

t_channel	get_pixel_color(t_rt *rt_data, t_dot pixel)
{
	t_ray		primary_ray;
	t_channel	color;
	t_intersect	closest_inter;

	primary_ray = compute_ray(rt_data->camera, pixel);
	closest_inter = find_closest_inter(rt_data, primary_ray);
	if (closest_inter.distance == INFINITY)
		color = (t_channel){0, 0, 0};
	else
		color = find_color(rt_data, closest_inter, primary_ray);
	return (color);
}

//----------------------------------------------------------------------------- */
/*
int		draw_scene(t_rt *rt_data)
{
	t_dot	pixel;
	pixel.y = 0;
	while (pixel.y < WIN_SIZE)
	{
		pixel.x = 0;
		while (pixel.x < WIN_SIZE)
		{
			draw_pixel_with_aa(rt_data, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
	return (0);
}
void	draw_pixel_with_aa(t_rt *rt_data, t_dot pixel)
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
*/
