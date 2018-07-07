/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_calculation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:41:17 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/05 16:41:18 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_functions.h"

static int	biling_phong_calculation(t_vector nor, t_ray s_ray, t_light *light, t_vector h)
{
	int		col_b;
	int		col_g;
	int		col_r;
	double	nor_li;
	double	w;

	nor_li = scalar_dob(nor, s_ray.direct);
	w = fmax(0, scalar_dob(nor, h));
	w = pow(w, 100);
	// w = 0;
	col_b = fmin(0xFF, (light->color & 255) * fmax(0, nor_li) * light->intence
	+ (light->color & 255) * w * light->intence);
	col_g = fmin(0xFF, (light->color >> 8 & 255) * fmax(0, nor_li) *
	light->intence + (light->color >> 8 & 255) * w * light->intence);
	col_r = fmin(0xFF, (light->color >> 16 & 255) * fmax(0, nor_li) *
	light->intence + (light->color >> 16 & 255) * w * light->intence);
	return (col_b + (col_g * 256) + (col_r * 256 * 256));
}

static int	ambient_light(int shape_col, t_light *light)
{
	int		col_b;
	int		col_g;
	int		col_r;
	double	k;

	k = 0;
	while (light)
	{
		k = fmax(light->intence / 2, k);
		light = light->next;
	}
	col_b = fmax(0, (shape_col & 255) * k);
	col_g = fmax(0, (shape_col >> 8 & 255) * k);
	col_r = fmax(0, (shape_col >> 16 & 255) * k);
	return (col_b + (col_g * 256) + (col_r * 256 * 256));
}

int			color_add(int first, int second)
{
	int sum;

	sum = fmin(0xFF, (first & 255) + (second & 255));
	sum += fmin(0xFF, (first >> 8 & 255) + (second >> 8 & 255)) * 256;
	sum += fmin(0xFF, (first >> 16 & 255) + (second >> 16 & 255)) * 256 * 256;
	return (sum);
}

static int	not_in_the_shadow(t_ray shadow_ray, t_rt *rt_data, t_light *light)
{
	double distance;
	t_shape *shapes;

	shapes = rt_data->shapes;
	while (shapes)
	{
		if (shapes->id != rt_data->intersected.shape->id &&
		(distance = shapes->find_distance(shadow_ray, shapes)) != MAX_LEN)
		{
			if ((!light->is_dir && distance < v_mod(sub_vectors(shadow_ray.origin,
			light->direct))) || light->is_dir)
				return (0);
		}
		shapes = shapes->next;
	}
	return (1);
}

// int				transperent_light(t_vector r, t_ray ray, t_light *li, t_shape *sh)
// {

// }

// int				zercal_light(t_vector nor, t_ray ray, t_rt *rt_data)
// {
// 	double		a;
// 	t_shape		*sh;
// 	int			color;
// 	int			color_to_scene;
// 	double		min;

// 	color = 0;
// 	if (rt_data->reflect_rate < rt_data->max_reflections)
// 	{
// 		(rt_data->reflect_rate)++;
// 		sh = rt_data->shapes;
// 		a = 2 * scalar_dob(nor, v_to_len(ray.rev_dir, -1, 0));
// 		nor = v_to_len(nor, a, 0);
// 		ray.direct = v_to_len(sub_vectors(v_to_len(ray.rev_dir, -1, 0), nor), 1, 0);
// 		min = MAX_LEN;
// 		while (sh)
// 		{
// 			if (sh->id != ray.id)
// 			{
// 				color = sh->inter(&ray, sh->shape, rt_data);
// 				if (ray.dest <= min)
// 				{
// 					min = ray.dest;
// 					color_to_scene = color;
// 				}
// 			}
// 			sh = sh->next;
// 		}
// 		color = color_to_scene;
// 		color = ((color & 255) / ray.mirror) + (((color >> 8 & 255) / ray.mirror)
// 		<< 8) + (((color >> 16 & 255) / ray.mirror) << 16);
// 	}
// 	return(color);
// }

int			shading_calculation(t_vector nor, t_ray ray, t_rt *rt_data)
{
	t_vector	h;
	int			color;
	t_light		*light;
	t_ray		shadow_ray;

	light = rt_data->light;
	color = ambient_light(rt_data->intersected.shape->color, rt_data->light);
	shadow_ray.origin = rt_data->intersected.intersect_point;
	// if (ray.mirror)
	// 	color = color_add(color, zercal_light(nor, ray, rt_data));
    // if (ray.transperent)
    //     color = color_add(color, transperent_light(nor, ray, light, sh));
	while (light)
	{
		if (light->is_dir)
			shadow_ray.direct = v_to_len(light->direct, -1, 0);
		else
			shadow_ray.direct = v_to_len(sub_vectors(light->direct, shadow_ray.origin), 1, 0);
		if (not_in_the_shadow(shadow_ray, rt_data, light))
		{
			h = add_vectors(v_to_len(ray.direct, -1, 0), shadow_ray.direct);
			h = v_to_len(h, 1, 0);
			color = color_add(color, biling_phong_calculation(nor, ray, light, h));
		}
		light = light->next;
	}
	return (color);
}
