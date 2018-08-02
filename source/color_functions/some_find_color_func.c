/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_find_color_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 20:07:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/01 15:28:45 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

int			is_shadows_here(t_ray light_ray, cl_float3 normal, t_ray r)
{
	float	is_light_with_cam;

	is_light_with_cam = vect_scalar_mult(r.direction, normal) *
	vect_scalar_mult(vect_mult_scalar(light_ray.direction, -1), normal);
	if (is_light_with_cam >= 0)
		return (TRUE);
	else
		return (FALSE);
}

t_channel	*distance_of_shadow(t_intersect tmp, t_cl_data cl_data)
{
	t_channel		*shadow;

	ft_bzero(&shadow, sizeof(t_channel));
	if (tmp.distance != INFINITY)
	{
		shadow = (t_channel *)ft_memalloc(sizeof(t_channel));
		get_texture(&tmp, cl_data);
		if (tmp.fig->transperent_coef)
			add_coef(shadow, tmp.texture_color, tmp.fig->transperent_coef);
		return (shadow);
	}
	return (NULL);
}

t_channel	*is_figure_first_inter_by_light(t_rt *rt_data, t_ray light_ray,
				t_intersect closest_inter, t_light *current_lamp)
{
	t_intersect		close_to_light;
	t_intersect		tmp;
	float			distance_to_light;
	int				current;

	current = -1;
	tmp.distance = INFINITY;
	distance_to_light = (current_lamp->type == POINT)
	? distance(current_lamp->origin, closest_inter.point) : INFINITY;
	while (++current < rt_data->cl_data.num_of_objects)
	{
		close_to_light.fig = &rt_data->objects_arr[current];
		if (close_to_light.fig != closest_inter.fig)
		{
			choose_intersection(light_ray, &close_to_light);
			if (close_to_light.distance != INFINITY)
				close_to_light.distance = (current_lamp->type == POINT) ?
distance(light_ray.origin, close_to_light.point) : close_to_light.distance;
			if (close_to_light.distance < distance_to_light)
				tmp = close_to_light;
		}
	}
	return (distance_of_shadow(tmp, rt_data->cl_data));
}

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
