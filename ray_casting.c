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

// void		pixel_add(t_rt *rt_data, int x, int y, unsigned int color)
// {
// 	int bpp;
// 	int size_l;
// 	int end;
// 	int *buff;

// 	if (x >= 0 && x < SCR_SIZE && y >= 0 && y < SCR_SIZE)
// 	{
// 		buff = (int *)mlx_get_data_addr(rt_data->img, &bpp, &size_l, &end);
// 		buff[SCR_SIZE * y + x] = color;
// 	}
// }

int			find_color_for_me_pleas(t_ray ray, t_rt *rt_data)
{
	double		distance;
	int			color_to_scene;
	t_shape		*shapes;
	t_vector	normal;

	shapes = rt_data->shapes;
	color_to_scene = 0;
	rt_data->intersected.distance = MAX_LEN;
	while (shapes)
	{
		rt_data->reflect_rate = 0;
		distance = shapes->find_distance(ray, shapes);
		if (distance < rt_data->intersected.distance)
		{
			rt_data->intersected.distance = distance;
			rt_data->intersected.shape = shapes;
			rt_data->intersected.intersect_point = add_vectors(ray.origin,
			v_to_len(ray.direct, distance, 0)); 
		}
		shapes = shapes->next;
	}
	normal = rt_data->intersected.shape->get_normal(ray, rt_data->intersected);
	color_to_scene = shading_calculation(normal, ray, rt_data);
	// rt_data->intersected.shape->make_shading(rt_data);
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

void		ray_casting(t_rt *rt_data)
{
	double		i;
	double		j;
	t_ray		ray;
	t_vector	v[3];
	int			color;

	j = (-1) * SCR_SIZE / 2;
	rt_data->camera.direct = v_to_len(rt_data->camera.direct, rt_data->camera.dest, 0);
	ray.origin = rt_data->camera.origin;
	while (j < SCR_SIZE / 2)
	{
		i = (-1) * SCR_SIZE / 2;
		while (i < SCR_SIZE / 2)
		{
			ray.direct = find_ray_direction(j, i, rt_data);
			color = find_color_for_me_pleas(ray, rt_data);
			// pixel_add(rt_data, i + SCR_SIZE / 2, j + SCR_SIZE / 2, color);
			i++;
		}
		j++;
	}
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
