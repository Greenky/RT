/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_find_color_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 20:07:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:59:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int			is_shadows_here(t_ray light_ray, t_vector normal, t_ray r)
{
	float	is_light_with_cam;

	is_light_with_cam = vect_scalar_mult(r.direction, normal) *
						vect_scalar_mult(vect_mult_scalar(light_ray.direction, -1), normal);
	if (is_light_with_cam >= 0)
		return (TRUE);
	else
		return (FALSE);
}

int			is_light_ray_cross_figure(t_rt *rt_data, int type_light, t_ray light_ray,
										t_intersect closest_inter)
{
	t_intersect		closest_to_light;
	float			distance_to_light;
	int				current;

	current = 0;
	if (type_light == SPOT)
	{
		light_ray.origin = light_ray.origin;
		light_ray.direction = light_ray.direction;
		distance_to_light = distance(light_ray.origin, closest_inter.point);
		while (current < rt_data->objects_num)
		{
			closest_to_light.fig = rt_data->objects_arr + current;
			if (closest_to_light.fig != closest_inter.fig)
			{
				choose_intersection(light_ray, &closest_to_light);
				if (closest_to_light.distance != INFINITY)
					closest_to_light.distance =
							distance(light_ray.origin, closest_to_light.point);
				if (closest_to_light.distance < distance_to_light)
					return (FALSE);
			}
			current++;
		}
	}
	else if (type_light == DIRECT)
	{
		while (current < rt_data->objects_num)
		{
			closest_to_light.fig = rt_data->objects_arr + current;
			if (closest_to_light.fig != closest_inter.fig)
			{
				choose_intersection(light_ray, &closest_to_light);
				if (closest_to_light.distance != INFINITY)
					return (FALSE);
			}
			current++;
		}
	}
	return (TRUE);
}

float		*find_cos_angle(t_vector light_dir, t_intersect closest_inter,
			t_vector normal, t_ray r)
{
	t_vector	light_ray_unit;
	float		*cos_angle;
	t_vector	bisector;

	cos_angle = malloc(sizeof(float) * 2);
	light_ray_unit = normalize_vector(light_dir);
	cos_angle[0] = vect_scalar_mult(light_ray_unit, normal);
	if (cos_angle[0] < 0)
		cos_angle[0] = 0;

	bisector = normalize_vector(vect_sum(r.direction, light_ray_unit));
	cos_angle[1] = (float)(pow(vect_scalar_mult(bisector, normal),
					closest_inter.fig->specular_coef) *
			pow(closest_inter.fig->specular_coef, 0.75) * 2);
	if (cos_angle[1] < 0)
		cos_angle[1] = 0;
	return (cos_angle);
}

uint32_t	fig_color_with_light_channel(float fig_color, float light_color)
{
	uint32_t	new_color;

	if (fig_color < 0 || light_color < 0)
		return (0);
	new_color = (uint32_t)(fig_color * light_color) >> 8;
	if (new_color > 0xFF)
		new_color = 0xFF;
	return (new_color);
}
