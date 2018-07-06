/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 14:31:48 by vmazurok          #+#    #+#             */
/*   Updated: 2018/04/27 14:31:49 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_data.h"

void		pixel_add(t_rt *rt_data, int x, int y, unsigned int color)
{
	int bpp;
	int size_l;
	int end;
	int *buff;

	if (x >= 0 && x < SCR_SIZE && y >= 0 && y < SCR_SIZE)
	{
		buff = (int *)mlx_get_data_addr(rt_data->img, &bpp, &size_l, &end);
		buff[SCR_SIZE * y + x] = color;
	}
}

int			find_color_for_me_pleas(t_ray ray, t_rt *rt_data)
{
	double	min;
	int		color;
	int		color_to_scene;
	t_shape	*shapes;

	shapes = rt_data->shapes;
	color_to_scene = 0;
	min = MAX_LEN;
	while (shapes)
	{
		rt_data->reflect_rate = 0;
		distance = shapes->find_distance(ray, shapes, rt_data);
		if (distance < rt_data->intersected.distance)
		{
			rt_data->intersected.distance = distance;
			rt_data->intersected.shape = shapes;
			rt_data->intersected.intersect_point = add_vectors(ray.origin,
			v_to_len(ray.direct, distance, 0)); 
		}
		shapes = shapes->next;
	}
	color_to_scene = rt_data->intersected.shape->make_shading(rt_data);
	return (color_to_scene);
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
			v[0] = v_to_len(rt_data->camera.up, j, 1);
			v[1] = v_to_len(rt_data->camera.right, i, 1);
			v[2] = add_vectors(v[0], v[1]);
			ray.direct = v_to_len(add_vectors(v[2], rt_data->camera.direct), 1, 0);
			color = find_color_for_me_pleas(ray, rt_data);
			pixel_add(rt_data, i + SCR_SIZE / 2, j + SCR_SIZE / 2, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(rt_data->mlx, rt_data->win, rt_data->img, 0, 0);
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
