/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pixel_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 20:39:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:58:59 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_functions.h"

uint32_t	find_color(t_cl_data cl_data, t_light *lights,
					t_objects *objects, t_intersect closest_inter, t_ray r)
{
	t_light			*current_lamp;
	t_channel		light_coef;
	int				current;
	float			i;

	ft_bzero(&light_coef, sizeof(t_channel));
	if (closest_inter.fig->is_cartoon)
	{
		i = vect_scalar_mult(r.direction,
		choose_normal(*closest_inter.fig, closest_inter.point));
		if (i < 0.2 && i >= 0)
			return (0xFFFFFF);
	}
	current = 0;
//	closest_inter.normal = choose_normal(*closest_inter.fig,
//										closest_inter.point);
	while (current < cl_data.num_of_lights)
	{
		current_lamp = (lights) + current;
		add_coef(&light_coef, find_lamp_coef(cl_data, objects, current_lamp,
		closest_inter, r, lights), 1);
		current++;
	}
	return (find_color_hex(light_coef, closest_inter));
}

void		add_coef(t_channel *coef1, t_channel coef2, float coef)
{
	coef1->blue += coef2.blue * coef;
	coef1->green += coef2.green * coef;
	coef1->red += coef2.red * coef;
}

t_intersect	find_closest_reflected_inter(t_cl_data cl_data,
						t_objects *objects, t_ray ray, t_objects *this)
{
	t_intersect	tmp_inter;
	t_intersect	closest_inter;
	int			current;

	closest_inter.distance = INFINITY;
	current = 0;
	while (current < cl_data.num_of_objects)
	{
		tmp_inter.fig = &objects[current];
		choose_intersection(ray, &tmp_inter);
		if (tmp_inter.distance < closest_inter.distance
			&& tmp_inter.fig != this)
			closest_inter = tmp_inter;
		current++;
	}
	get_texture(&closest_inter, cl_data);
	return (closest_inter);
}

t_channel	find_lamp_coef(t_cl_data cl_data,
				t_objects *objects, t_light *current_lamp,
				t_intersect closest_inter, t_ray r, t_light *lights)
{
	t_ray			reflected_ray;
	t_intersect		reflected_inter;
	float			a;
	t_ray			light_ray;
	t_channel		lamp_coef;
	float			*cos_angle;

	ft_bzero(&lamp_coef, sizeof(t_channel));
	if (current_lamp->type == AMBIENT)
		add_coef(&lamp_coef, current_lamp->color, current_lamp->intensity);
	else
	{
		light_ray = find_light_ray(current_lamp->origin, closest_inter.point);
		if (closest_inter.fig->mirror_coef > 0
			&& cl_data.reflect_rate < cl_data.max_reflections)
		{
			cl_data.reflect_rate++;
			reflected_ray.origin = closest_inter.point;
			a = 2 * vect_scalar_mult(r.direction, closest_inter.normal);
			reflected_ray.direction = vect_diff(r.direction,
					vect_mult_scalar(closest_inter.normal, a));
			reflected_inter = find_closest_reflected_inter(cl_data,
								objects, reflected_ray, closest_inter.fig);
			if (reflected_inter.distance != INFINITY)
				add_coef(&lamp_coef, int_to_channels(find_color(cl_data,
						lights, objects, reflected_inter, reflected_ray)),
						closest_inter.fig->mirror_coef);
		}
		if (!is_shadows_here(light_ray, closest_inter.normal, r) ||
		!is_figure_first_inter_by_light(cl_data,
							objects, light_ray, closest_inter))
			return (lamp_coef);
		cos_angle = find_cos_angle(light_ray,
					closest_inter, closest_inter.normal, r);
		add_coef(&lamp_coef, current_lamp->color, cos_angle[0] *
				current_lamp->intensity);
		add_coef(&lamp_coef, (t_channel){1, 1, 1}, cos_angle[1] *
				current_lamp->intensity);
		free(cos_angle);
	}
	return (lamp_coef);
}

t_ray		find_light_ray(cl_float3 origin, cl_float3 end)
{
	t_ray		light_ray;

	light_ray.origin = origin;
	light_ray.direction = vect_diff(end, origin);
	return (light_ray);
}
