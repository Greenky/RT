/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 14:31:48 by vmazurok          #+#    #+#             */
/*   Updated: 2018/04/27 14:31:49 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_functions.h"

void		pixel_add(t_rt *rt_data, int x, int y, unsigned int color)
{
	// int bpp;
	// int size_l;
	// int end;
	// int *buff;

	if (x >= 0 && x < SCR_SIZE && y >= 0 && y < SCR_SIZE)
	{
		/*
		buff = (int *)mlx_get_data_addr(rt_data->img, &bpp, &size_l, &end);
		buff[SCR_SIZE * y + x] = color;
		*/
		((int *)rt_data->surface->pixels)[y * SCR_SIZE + x] = color;
	}
}

int			find_color_for_me_pleas(t_ray ray, t_rt *rt_data)
{
	double			distance;
	int				color_to_scene;
	t_shape			*shapes;
	t_intersected	intersected;

	shapes = rt_data->shapes;
	color_to_scene = 0;
	intersected.distance = MAX_LEN;
	while (shapes)
	{
		rt_data->reflect_rate = 0;
		distance = shapes->find_distance(ray, shapes);
		if (distance < intersected.distance)
		{
			intersected.distance = distance;
			intersected.shape = shapes;
			intersected.intersect_point = add_vectors(ray.origin, v_to_len(ray.direct, distance, 0));
		}
		shapes = shapes->next;
	}
	// printf("time to shading\n");
	// --------------------------------------------

	// printf("camera.o - (%f, %f, %f) ____ camera.d - (%f, %f, %f)\n",
	// rt_data->camera.origin.x, rt_data->camera.origin.y, rt_data->camera.origin.z,
	// rt_data->camera.direct.x, rt_data->camera.direct.y, rt_data->camera.direct.z);
	// while (rt_data->light)
	// {
	// 	printf("light!!\n");
	// 	printf("light.dir - (%f, %f, %f) ____ int - %f\n",
	// 	rt_data->light->direct.x, rt_data->light->direct.y, rt_data->light->direct.z, 
	// 	rt_data->light->intence);
	// 	rt_data->light = rt_data->light->next;
	// }
	// printf("\n");
	// while (rt_data->shapes)
	// {
	// 	printf("shape!!\n");
	// 	printf("shape.name - %c ____ int - %i\n",
	// 	rt_data->shapes->name, rt_data->shapes->id);
	// 	rt_data->shapes = rt_data->shapes->next;
	// }
	// exit(1);
	// printf("intersected dist - %f\n shape name - %c\n point - (%f, %f, %f)", 
	// intersected.distance, intersected.shape->name, intersected.shape->direct.x, 
	// intersected.shape->direct.y, intersected.shape->direct.z);
	// --------------------------------------------
	if (intersected.distance != MAX_LEN)
	{
		intersected.normal = intersected.shape->get_normal(ray, intersected);
		color_to_scene = shading_calculation(intersected, ray, rt_data);
	}
	return (color_to_scene);
}

t_vector	find_ray_direction(double j, double i, t_rt *rt_data)
{
	t_vector up_vector;
	t_vector right_vector;
	t_vector sum_vector;

	up_vector = v_to_len(rt_data->camera.up, j, 1);
	right_vector = v_to_len(rt_data->camera.right, i, 1);
	sum_vector = add_vectors(add_vectors(up_vector, right_vector), rt_data->camera.direct);
	return(v_to_len(sum_vector, 1, 0));
}

//--------------------------------------------------------
void		event_management(t_rt *scene, SDL_Event *event)
{
	int		running;

	running = 1;
	SDL_UpdateWindowSurface(scene->window);
	while (running)
	{
		while (SDL_PollEvent(event))
		{
			if (!exit_x(scene, event))
				running = 0;
			else if (event->type == SDL_KEYDOWN)
				key_down(scene, event);
		}
	}
}

int			exit_x(t *scene, SDL_Event *event)
{
	if (event->type == SDL_QUIT
		|| (event->type == SDL_KEYDOWN &&
		event->key.keysym.scancode == SDL_SCANCODE_ESCAPE))
	{
		ft_lstdel(&(scene->lights), &free);
		ft_lstdel(&(scene->lights), &free);
		SDL_FreeSurface(scene->screen_surface);
		SDL_DestroyWindow(scene->window);
		SDL_Quit();
		return (0);
	}
	else
		return (1);
}
//-------------------------------------------------------

void		ray_casting(t_rt *rt_data)
{
	double		i;
	double		j;
	t_ray		ray;
	int			color;
	SDL_Event	event;

	j = (-1) * SCR_SIZE / 2;
	rt_data->camera.direct = v_to_len(rt_data->camera.direct, rt_data->camera.dest, 0);
	ray.origin = rt_data->camera.origin;
	// while (rt_data->shapes)
	// {
	// 	printf("name - %c, id - %i\n", rt_data->shapes->name, rt_data->shapes->id);
	// 	rt_data->shapes = rt_data->shapes->next;
	// }
	while (j < SCR_SIZE / 2)
	{
		i = (-1) * SCR_SIZE / 2;
		while (i < SCR_SIZE / 2)
		{
			ray.direct = find_ray_direction(j, i, rt_data);
			color = find_color_for_me_pleas(ray, rt_data);
			pixel_add(rt_data, i + SCR_SIZE / 2, j + SCR_SIZE / 2, color);
			i++;
		}
		j++;
	}
	printf("good\n");
	SDL_UpdateWindowSurface(rt_data->window);
	event_management(scene, &event);
	// mlx_put_image_to_window(rt_data->mlx, rt_data->win, rt_data->img, 0, 0);
}

void		add_shape(t_rt *rt_data, t_shape *shape)
{
	t_shape	*step;

	shape->next = NULL;
	step = rt_data->shapes;
	if (step)
	{
		while (step->next)
			step = step->next;
		step->next = shape;
	}
	else
		rt_data->shapes = shape;
}
