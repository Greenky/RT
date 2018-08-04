/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pixel_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 20:39:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/02 17:23:13 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

t_channel	find_color(t_rt *rt_data,
					t_cl_data cl_data, t_intersect closest_inter, t_ray r)
{
	t_light			*current_lamp;
	t_channel		light_coef;
	int				current;
//	float			i;

	ft_bzero(&light_coef, sizeof(t_channel));
	current = 0;
	while (current < rt_data->cl_data.num_of_lights)
	{
		current_lamp = (rt_data->lights_arr) + current;
		cl_data.current_lamp = current_lamp;
		add_coef(&light_coef,
				find_lamp_coef(rt_data, cl_data, closest_inter, r), 1);
		current++;
	}
	return (fig_color_with_light(light_coef, closest_inter));
}

void		add_coef(t_channel *coef1, t_channel coef2, float coef)
{
	coef1->blue += coef2.blue * coef;
	coef1->green += coef2.green * coef;
	coef1->red += coef2.red * coef;
}

t_intersect	find_closest_reflected_inter(t_rt *rt_data,
									t_ray ray, t_objects *this)
{
	t_intersect	tmp_inter;
	t_intersect	closest_inter;
	int			current;

	closest_inter.distance = INFINITY;
	current = 0;
	while (current < rt_data->cl_data.num_of_objects)
	{
		tmp_inter.fig = &(rt_data->objects_arr)[current];
		choose_intersection(ray, &tmp_inter);
		if (tmp_inter.distance < closest_inter.distance
			&& tmp_inter.fig != this)
			closest_inter = tmp_inter;
		current++;
	}
	get_texture(&closest_inter, rt_data->cl_data);
	return (closest_inter);
}

t_ray		find_light_ray(cl_float3 origin, t_light *light)
{
	t_ray		light_ray;

	light_ray.origin = origin;
	if (light->type == POINT)
		light_ray.direction =
		normalize_vector(vect_diff(light->origin, origin));
	else
		light_ray.direction = normalize_vector(light->direct);
	return (light_ray);
}
