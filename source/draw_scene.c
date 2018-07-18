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

//* THREADS  for debug ----------------------------------------------

#include <pthread.h>
#define THREAD_MAX 20
typedef struct		s_thread_data
{
	t_rt			*scene;
	int				string_num;
}					t_thread_data;

void	*draw_strings(void *thread_data_void);
void	set_tread_param(t_rt *scene, t_thread_data *thread_num);

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
			draw_pixel(thread_data->scene, thread_data->scene->cl_data, thread_data->scene->objects_arr, thread_data->scene->lights_arr, pixel);
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

void	draw_pixel(t_rt *rt_data, t_cl_data cl_data, t_objects *objects, t_light *lights, t_dot pixel)
{
	t_ray		primary_ray;
	uint32_t	color;
	t_intersect	closest_inter;

	primary_ray = compute_ray(cl_data.camera, pixel);
	closest_inter = find_closest_inter(cl_data, objects, primary_ray);
	rt_data->cl_data.reflect_rate = 0;
	if (closest_inter.distance == INFINITY)
		color = 0;
	else
		color = find_color(rt_data->cl_data, lights, objects, closest_inter, primary_ray);
	set_pixel(rt_data->screen_surface, pixel.x, pixel.y, color);
}
//----------------------------------------------------------------------------- */

/*
int		draw_scene(t_rt *rt_data)
{
	t_dot	pixel;
	pixel.y = 0;
	while (pixel.y < SCR_SIZE)
	{
		pixel.x = 0;
		while (pixel.x < SCR_SIZE)
		{
			draw_pixel(rt_data, rt_data->cl_data, rt_data->objects_arr, rt_data->lights_arr, pixel);
			pixel.x++;
		}

		pixel.y++;
	}
	return (0);
}
void	draw_pixel(t_rt *rt_data, t_cl_data cl_data, t_objects *objects, t_light *lights, t_dot pixel)
{
	t_ray		primary_ray;
	uint32_t	color;
	t_intersect	closest_inter;

	primary_ray = compute_ray(cl_data.camera, pixel);
	closest_inter = find_closest_inter(cl_data, objects, primary_ray);
	rt_data->cl_data.reflect_rate = 0;
	if (closest_inter.distance == INFINITY)
		color = 0;
	else
		color = find_color(rt_data->cl_data, lights, objects, closest_inter, primary_ray);
	set_pixel(rt_data->screen_surface, pixel.x, pixel.y, color);
}
//*/
