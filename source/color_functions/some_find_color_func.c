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

#include "../includes/rt_functions.h"

int			is_shadows_here(t_ray light_ray, cl_float3 normal, t_ray r)
{
	float	is_light_with_cam;

	is_light_with_cam = vect_scalar_mult(r.direction, normal) *
						-vect_scalar_mult(light_ray.direction, normal);
	if (is_light_with_cam >= 0)
		return (TRUE);
	else
		return (FALSE);
}

int			is_figure_first_inter_by_light(t_cl_data cl_data,
											  t_objects *objects, t_ray light_ray, t_intersect closest_inter, t_channel *shadow, float dist)
{
	t_intersect		close_to_light;
	t_intersect		tmp;
	float			distance_to_light;
	int				current;

	current = 0;
	tmp.distance = INFINITY;
	distance_to_light = dist;
	while (current < cl_data.num_of_objects)
	{
		close_to_light.fig = &objects[current];
		if (close_to_light.fig != closest_inter.fig)
		{
			choose_intersection(light_ray, &close_to_light);
			if (close_to_light.distance != INFINITY)
				close_to_light.distance =
						distance(light_ray.origin, close_to_light.point);
			if (close_to_light.distance < distance_to_light)
			{
				tmp = close_to_light;
			}
		}
		current++;
	}
	if (tmp.distance != INFINITY)
	{
		get_texture(&tmp, cl_data);
		if (tmp.fig->transperent_coef)
			add_coef(shadow, tmp.texture_color, tmp.fig->transperent_coef);
		return (FALSE);
	}
	return (TRUE);
}

//int			is_figure_first_inter_by_light(t_cl_data cl_data,
//				t_objects *objects, t_ray light_ray, t_intersect closest_inter, t_channel *shadow, float dist)
//{
//	t_intersect		close_to_light;
////	t_intersect		tmp_inter;
//	float			distance_to_light;
//	int				current;
//
//	current = 0;
//	distance_to_light = dist;
//	while (current < cl_data.num_of_objects)
//	{
//		close_to_light.fig = &objects[current];
//		if (close_to_light.fig != closest_inter.fig)
//		{
//			choose_intersection(light_ray, &close_to_light);
//			if (close_to_light.distance < distance_to_light)
//			{
//				get_texture(&close_to_light, cl_data);
//				if (close_to_light.fig->transperent_coef)
//					add_coef(shadow, close_to_light.texture_color, close_to_light.fig->transperent_coef);
//				return (FALSE);
//			}
//		}
//		current++;
//	}
//	return (TRUE);
//}

float		*find_cos_angle(t_ray light_ray, t_intersect closest_inter,
							 cl_float3 normal, t_ray r)
{
	cl_float3		light_ray_unit;
	float			*cos_angle;
	cl_float3		bisector;

	cos_angle = malloc(sizeof(float) * 2);
	light_ray_unit = normalize_vector(light_ray.direction);
	light_ray_unit = vect_mult_scalar(light_ray_unit, -1);
	cos_angle[0] = vect_scalar_mult(light_ray_unit, normal);
	if (cos_angle[0] < 0)
		cos_angle[0] = 0;
	bisector = normalize_vector(vect_sum(r.direction, light_ray_unit));
	cos_angle[1] = (float)(pow(vect_scalar_mult(bisector, normal),
							   closest_inter.fig->bling_phong) *
						   pow(closest_inter.fig->bling_phong, 0.75) * 2);
	if (cos_angle[1] < 0)
		cos_angle[1] = 0;
	return (cos_angle);
}

uint32_t	find_color_hex(t_channel light_coef, t_intersect closest_inter)
{
	uint32_t	color_hex;

	color_hex = 0;
	color_hex += find_color_channel(closest_inter.texture_color.red,
									light_coef.red, 16);
	color_hex += find_color_channel(closest_inter.texture_color.green,
									light_coef.green, 8);
	color_hex += find_color_channel(closest_inter.texture_color.blue,
									light_coef.blue, 0);
	return (color_hex);
}

uint32_t	find_color_channel(float fig_color_channel,
							   float light_color_channel, int step)
{
	uint32_t	mult;

	if (fig_color_channel < 0 || light_color_channel < 0)
		return (0);
	mult = (uint32_t)(fig_color_channel * light_color_channel) >> 8;
	if (mult > 0xFF)
		mult = 0xFF;
	return (mult << step);
}