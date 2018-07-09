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

#include "../inc/rtv1.h"

int		draw_all_scene(t_scene_data *scene)
{
	pthread_t		threads[THREAD_MAX - 1];
	t_thread_data	thread_num[THREAD_MAX];
	int				idx;

	set_tread_param(scene, thread_num);
	idx = 0;
	while (idx < THREAD_MAX - 1)
	{
		pthread_create(&threads[idx], NULL, draw_strings,
						(thread_num + idx));
		idx++;
	}
	draw_strings((thread_num + THREAD_MAX - 1));
	idx = 0;
	while (idx < THREAD_MAX - 1)
		pthread_join(threads[idx++], NULL);
	return (0);
}

void	*draw_strings(void *thread_data_void)
{
	t_dot			pixel;
	t_thread_data	*thread_data;
	t_scene_data	*scene;

	thread_data = (t_thread_data*)thread_data_void;
	scene = thread_data->scene;
	pixel.y = thread_data->string_num;
	while (pixel.y < WIN_HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIN_WIDTH)
		{
			draw_pixel(scene, pixel);
			pixel.x++;
		}
		pixel.y += THREAD_MAX;
	}
	return (NULL);
}

void	set_tread_param(t_scene_data *scene, t_thread_data *thread_num)
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

void	draw_pixel(t_scene_data *scene, t_dot pixel)
{
	t_ray		primary_ray;
	uint32_t	color;
	t_intersect	closest_inter;

	primary_ray = compute_ray(scene->camera, pixel);
	closest_inter = find_closest_inter(scene, primary_ray);
	if (closest_inter.distance == INFINITY)
		color = 0;
	else
		color = find_color(scene, closest_inter, primary_ray);
	set_pixel(scene->screen_surface, pixel.x, pixel.y, color);
}
