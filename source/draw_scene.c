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

int		draw_scene(t_rt *scene)
{
	pthread_t		threads[THREAD_MAX];
	t_thread_data	thread_num[THREAD_MAX];
	int				idx;

	set_tread_param(scene, thread_num);
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
	if (scene->take_screenshot == 0)
	{
		draw_clicked_info(scene);
		draw_gui(scene);
	}
	return (0);
}

void	*draw_strings(void *thread_data_void)
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
			draw_pixel(thread_data->scene,
				thread_data->scene->objects_arr,
					thread_data->scene->lights_arr, pixel);
			pixel.x++;
		}
		pixel.y += THREAD_MAX;
	}
	return (NULL);
}

void	set_tread_param(t_rt *scene, t_thread_data *thread_num)
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

//int		apply_filter(double r, double g, double b, double filter)
//{
//	double	res;
//	double	tr;
//	double	tg;
//	double	tb;
//
//	if (filter == gray)
//	{
//		res = r * 0.299 + g * 0.587 + b * 0.114;
//		return ((int)res << 16 | (int)res << 8 | (int)res);
//	}
//	if (filter == sepia)
//	{
//		tr = 0.393 * r + 0.769 * g + 0.189 * b;
//		tg = 0.349 * r + 0.686 * g + 0.168 * b;
//		tb = 0.272 * r + 0.534 * g + 0.131 * b;
//		r = (tr > 255) ? 255 : tr;
//		g = (tg > 255) ? 255 : tg;
//		b = (tb > 255) ? 255 : tb;
//	}
//	if (filter == inversion)
//		return (0xFFFFFF - ((int)r << 16 | (int)g << 8 | (int)b));
//	return ((int)r << 16 | (int)g << 8 | (int)b);
//}

//int		apply_to_rgb(double li, int color, int filter)
//{
//	double	r;
//	double	g;
//	double	b;
//
//	r = ((color >> 16) & 0xFF) * li;
//	if (r > 255)
//		r = 255;
//	g = ((color >> 8) & 0xFF) * li;
//	if (g > 255)
//		g = 255;
//	b = (color & 0xFF) * li;
//	if (b > 255)
//		b = 255;
//	return (apply_filter(r, g, b, filter));
//}

uint32_t	apply_filter(uint32_t color, int filter)
{
//	uint32_t	r;
//	uint32_t	g;
//	uint32_t	b;
	t_channel	clr;
	t_channel	tmp;

	if (filter == NEGATIVE)
		return (0xFFFFFF - color);
//	r = (color >> 16) & 0xFF;
//	g = (color >> 8) & 0xFF;
//	b = color & 0xFF;
	clr = int_to_channels(color);
	if (filter == GREYSCALE)
	{
		color = (uint32_t)(clr.red * 0.299 + clr.green * 0.587 + clr.blue * 0.114);
		return (color << 16 | color << 8 | color);
	}
	if (filter == SEPIA)
	{
		tmp.red = (uint32_t)(0.393 * clr.red + 0.769 * clr.green + 0.189 * clr.blue);
		tmp.green = (uint32_t)(0.349 * clr.red + 0.686 * clr.green + 0.168 * clr.blue);
		tmp.blue = (uint32_t)(0.272 * clr.red + 0.534 * clr.green + 0.131 * clr.blue);
		clr.red = (uint32_t)((tmp.red > 255) ? 255 : tmp.red);
		clr.green = (uint32_t)((tmp.green > 255) ? 255 : tmp.green);
		clr.blue = (uint32_t)((tmp.blue > 255) ? 255 : tmp.blue);
//		clr.red = find_color_channel(tmp.red, 1, 16);
//		clr.green = find_color_channel(tmp.green, 1, 8);
//		clr.blue = find_color_channel(tmp.blue, 1, 0);
		return ((uint32_t)clr.red << 16 | (uint32_t)clr.green << 8 | (uint32_t)clr.blue);
	}
	return (color);
}

void	draw_pixel(t_rt *rt_data,
				   t_objects *objects, t_light *lights, t_dot pixel)
{
	t_ray		primary_ray;
	uint32_t	color;
	t_intersect	closest_inter;

	primary_ray = compute_ray(rt_data->cl_data.camera, pixel);
	closest_inter = find_closest_inter(rt_data->cl_data, objects, primary_ray);
	rt_data->cl_data.max_reflections = 5;
	rt_data->cl_data.reflect_rate = 0;
	if (closest_inter.distance == INFINITY)
		color = 0;
	else
		color = find_color(rt_data->cl_data, lights, objects, closest_inter, primary_ray);
	if (rt_data->filter != -1)
		color = apply_filter(color, rt_data->filter);
	set_pixel(rt_data->screen_surface, pixel.x, pixel.y, color);
}
