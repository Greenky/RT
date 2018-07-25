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

int			draw_scene(t_rt *scene)
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

/*
**int		draw_scene(t_rt *rt_data)
**{
**	t_dot	pixel;
**	pixel.y = 0;
**	while (pixel.y < SCR_SIZE)
**	{
**		pixel.x = 0;
**		while (pixel.x < SCR_SIZE)
**		{
**			draw_pixel(rt_data, rt_data->objects_arr,
** rt_data->lights_arr, pixel);
**			pixel.x++;
**		}
**		pixel.y++;
**	}
**	return (0);
**}
**void	draw_pixel(t_rt *rt_data, t_objects *objects,
** t_light *lights, t_dot pixel)
**{
**	t_ray		primary_ray;
**	uint32_t	color;
**	t_intersect	closest_inter;
**	primary_ray = compute_ray(rt_data->cl_data.camera, pixel);
**	closest_inter = find_closest_inter(rt_data->cl_data, objects, primary_ray);
**	rt_data->cl_data.reflect_rate = 0;
**	if (closest_inter.distance == INFINITY)
**		color = 0;
**	else
**		color = find_color(rt_data->cl_data, lights, objects,
** closest_inter, primary_ray);
**	set_pixel(rt_data->screen_surface, pixel.x, pixel.y, color);
**}
*/

void		*draw_strings(void *thread_data_void)
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
			draw_pixel(thread_data->scene, pixel);
			pixel.x++;
		}
		pixel.y += THREAD_MAX;
	}
	return (NULL);
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

void		draw_pixel(t_rt *rt_data, t_dot pixel)
{
	t_ray		primary_ray;
	uint32_t	color;
	t_intersect	closest_inter;
//	(void)lights;
	primary_ray = compute_ray(rt_data->cl_data.camera, pixel);
	closest_inter = find_closest_inter(rt_data->cl_data, rt_data->objects_arr, primary_ray);
	rt_data->cl_data.max_reflections = 5;
	rt_data->cl_data.reflect_rate = 0;
	if (closest_inter.distance == INFINITY)
		color = 0;
	else
		color = find_color(rt_data, rt_data->cl_data,closest_inter, primary_ray);
	if (rt_data->filter != -1)
		color = apply_filter(color, rt_data->filter);
	set_pixel(rt_data->screen_surface, pixel.x, pixel.y, color);
}
