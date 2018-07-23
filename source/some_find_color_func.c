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
						vect_scalar_mult(light_ray.direction, normal);
	if (is_light_with_cam >= 0)
		return (TRUE);
	else
		return (FALSE);
}

float		is_figure_first_inter_by_light(t_cl_data cl_data, t_objects *objects, t_ray light_ray,
										t_intersect closest_inter, t_channel *trancparent_add)
{
	t_intersect		clost_to_light;
	float			distance_to_light;
	int				current;

	current = 0;
	distance_to_light = distance(light_ray.origin, closest_inter.point);
	while (current < cl_data.num_of_objects)
	{
		clost_to_light.fig = &objects[current];
		if (clost_to_light.fig != closest_inter.fig)
		{
			choose_intersection(light_ray, &clost_to_light);
			if (clost_to_light.distance != INFINITY)
				clost_to_light.distance =
						distance(light_ray.origin, clost_to_light.point);
			if (clost_to_light.distance < distance_to_light)
            {
                add_coef(trancparent_add, clost_to_light.texture_color, clost_to_light.fig->transperent_coef);
                return (TRUE);
            }
		}
		current++;
	}
	return (FALSE);
}

float		*find_cos_angle(t_ray light_ray, t_intersect closest_inter,
			cl_float3 normal, t_ray r)
{
	cl_float3		light_ray_unit;
	float			*cos_angle;
	cl_float3		bisector;

	cos_angle = malloc(sizeof(float) * 2);
	light_ray_unit = normalize_vector(light_ray.direction);
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
