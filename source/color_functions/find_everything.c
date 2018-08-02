/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 19:52:05 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/25 19:52:07 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

t_channel	find_transparent(t_rt *rt_data,
				t_cl_data cl_data, t_intersect closest_inter, t_ray r)
{
	t_ray			transparent_ray;
	t_intersect		transparent_inter;
	t_channel		lamp_coef;

	ft_bzero(&lamp_coef, sizeof(t_channel));
	if (closest_inter.fig->transperent_coef > 0 && cl_data.trancparent_rate
	< cl_data.max_trancparent)
	{
		cl_data.trancparent_rate++;
		transparent_ray.origin = closest_inter.point;
		transparent_ray.direction = r.direction;
		transparent_inter =
			find_closest_reflected_inter(rt_data,
								transparent_ray, closest_inter.fig);
		if (transparent_inter.distance != INFINITY)
			add_coef(&lamp_coef,
			find_color(rt_data, cl_data, transparent_inter, transparent_ray),
					closest_inter.fig->transperent_coef);
	}
	return (lamp_coef);
}

t_channel	find_reflection(t_rt *rt_data,
					t_cl_data cl_data, t_intersect closest_inter, t_ray r)
{
	t_ray			reflected_ray;
	t_intersect		reflected_inter;
	float			a;
	t_channel		lamp_coef;

	ft_bzero(&lamp_coef, sizeof(t_channel));
	if (closest_inter.fig->mirror_coef > 0
		&& cl_data.reflect_rate < cl_data.max_reflections)
	{
		(cl_data.reflect_rate)++;
		reflected_ray.origin = closest_inter.point;
		a = 2 * vect_scalar_mult(r.direction, closest_inter.normal);
		reflected_ray.direction = vect_diff(r.direction,
			vect_mult_scalar(closest_inter.normal, a));
		reflected_inter = find_closest_reflected_inter(rt_data,
						reflected_ray, closest_inter.fig);
		if (reflected_inter.distance != INFINITY)
			add_coef(&lamp_coef,
					find_color(rt_data,
					cl_data, reflected_inter, reflected_ray),
					closest_inter.fig->mirror_coef);
	}
	return (lamp_coef);
}

t_channel	cos_angle_coef(t_cl_data cl_data,
							t_intersect closest_inter, t_ray r)
{
	t_channel		lamp_coef;
	t_ray			light_ray;
	float			*cos_angle;

	ft_bzero(&lamp_coef, sizeof(t_channel));
	light_ray = find_light_ray(closest_inter.point, cl_data.current_lamp);
	cos_angle = find_cos_angle(light_ray,
					closest_inter, closest_inter.normal, r);
	add_coef(&lamp_coef, cl_data.current_lamp->color, cos_angle[0] *
					cl_data.current_lamp->intensity);
	add_coef(&lamp_coef, (t_channel){1, 1, 1}, cos_angle[1] *
					cl_data.current_lamp->intensity);
	free(cos_angle);
	return (lamp_coef);
}

t_channel	hate_norminette(t_rt *rt_data,
				t_cl_data cl_data, t_intersect closest_inter, t_ray r)
{
	t_channel	lamp_coef;

	ft_bzero(&lamp_coef, sizeof(t_channel));
	add_coef(&lamp_coef, find_transparent(rt_data,
							cl_data, closest_inter, r), 1);
	add_coef(&lamp_coef, find_reflection(rt_data,
							cl_data, closest_inter, r), 1);
	return (lamp_coef);
}

t_channel	find_lamp_coef(t_rt *rt_data, t_cl_data cl_data,
							t_intersect closest_inter, t_ray r)
{
	t_ray			light_ray;
	t_channel		lamp_coef;
	t_channel		*shadow_col;

	shadow_col = NULL;
	ft_bzero(&lamp_coef, sizeof(t_channel));
	if (cl_data.current_lamp->type == AMBIENT)
		add_coef(&lamp_coef, cl_data.current_lamp->color,
				cl_data.current_lamp->intensity);
	else
	{
		light_ray = find_light_ray(closest_inter.point, cl_data.current_lamp);
		add_coef(&lamp_coef,
				hate_norminette(rt_data, cl_data, closest_inter, r), 1);
		if (!is_shadows_here(light_ray, closest_inter.normal, r) ||
			(shadow_col = is_figure_first_inter_by_light(rt_data,
						light_ray, closest_inter, cl_data.current_lamp)))
		{
			shadow_col ? add_coef(&lamp_coef, *shadow_col, 0.5) : 0;
			free(shadow_col);
			return (lamp_coef);
		}
		add_coef(&lamp_coef, cos_angle_coef(cl_data, closest_inter, r), 1);
	}
	return (lamp_coef);
}
