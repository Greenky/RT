/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:26:43 by vmazurok          #+#    #+#             */
/*   Updated: 2018/07/26 16:53:32 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

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

void		draw_pixel_pixel(t_rt *rt_data, t_dot pixel)
{
	t_ray			primary_ray;
	uint32_t		color;
	t_intersect		closest_inter;

	primary_ray = compute_ray(rt_data->cl_data.camera, pixel);
	closest_inter = find_closest_inter(rt_data->cl_data,
									rt_data->objects_arr, primary_ray);
	rt_data->cl_data.max_reflections = 5;
	rt_data->cl_data.reflect_rate = 0;
	if (closest_inter.distance == INFINITY)
		color = 0;
	else
		color = find_color(rt_data,
					rt_data->cl_data, closest_inter, primary_ray);
	if (rt_data->filter != -1)
		color = apply_filter(color, rt_data->filter);
	set_pixel(rt_data->screen_surface, pixel.x, pixel.y, color);
	int	x = pixel.x - 1;//TODO fix
	int	y = pixel.y - 1;//TODO fix
	while(++y < pixel.y + 10 && y < SCR_SIZE)
		while (++x < pixel.x + 10 && x < SCR_SIZE)
			set_pixel(rt_data->screen_surface, x, y, color);
}
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
			scene->filter == PIXEL ? draw_pixel_strings : draw_strings,
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

void		draw_pixel(t_rt *rt_data, t_dot pixel)
{
	t_ray		primary_ray;
	uint32_t	color;
	t_intersect	closest_inter;


	primary_ray = compute_ray(rt_data->cl_data.camera, pixel);

	closest_inter = find_closest_inter(rt_data->cl_data,
									rt_data->objects_arr, primary_ray);
	rt_data->cl_data.max_reflections = 5;
	rt_data->cl_data.max_trancparent = 5;
	rt_data->cl_data.reflect_rate = 0;
	rt_data->cl_data.trancparent_rate = 0;
	if (closest_inter.distance == INFINITY)
		color = 0;
	else
		color = find_color(rt_data,
						rt_data->cl_data, closest_inter, primary_ray);
	if (rt_data->filter != -1)
		color = apply_filter(color, rt_data->filter);
	set_pixel(rt_data->screen_surface, pixel.x, pixel.y, color);
}



/*int		draw_scene(t_rt *rt_data)
{
	int				idx;
	idx = 0;


	t_dot	pixel;
	pixel.y = 0;
	while (pixel.y < SCR_SIZE)
	{
		pixel.x = 0;
		while (pixel.x < SCR_SIZE)
		{
			draw_pixel(rt_data, pixel);
			if (pixel.x > 144)
			{
				system("leaks RT");
				exit(0);
			}
			pixel.x++;
		}

		pixel.y++;
	}
	if (rt_data->take_screenshot == 0)
	{
		draw_clicked_info(rt_data);
		draw_gui(rt_data);
	}
	return (0);
}



void	draw_pixel(t_rt *rt_data, t_dot pixel)
{
	t_ray		primary_ray;
	uint32_t	color;
	t_intersect	closest_inter;

	primary_ray = compute_ray(rt_data->cl_data.camera, pixel);
	closest_inter = find_closest_inter(rt_data->cl_data,
									   rt_data->objects_arr, primary_ray);
	rt_data->cl_data.max_reflections = 5;
	rt_data->cl_data.max_trancparent = 5;
	rt_data->cl_data.reflect_rate = 0;
	rt_data->cl_data.trancparent_rate = 0;
	if (closest_inter.distance == INFINITY)
		color = 0;
	else
		color = find_color(rt_data,
						   rt_data->cl_data, closest_inter, primary_ray);
	if (rt_data->filter != -1)
		color = apply_filter(color, rt_data->filter);
	set_pixel(rt_data->screen_surface, pixel.x, pixel.y, color);

}*/
