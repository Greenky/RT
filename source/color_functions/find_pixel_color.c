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

#include "../../includes/rt_functions.h"

t_channel	find_color(t_rt *rt_data, t_intersect closest_inter, t_ray r)
{
//	t_light		*tmp_node;
	t_light		*current_lamp;
	t_channel	light_coef;
	int			current;
	t_channel	final_color;

	ft_bzero(&light_coef, sizeof(t_channel));
//	float i = vect_scalar_mult(vect_mult_scalar(rt_data->camera.initial_basis.b_z, -1),
//	choose_normal(closest_inter.fig, closest_inter.point));
//	if (i < 0.3 && i >= 0)
//		return (0xFFFFFF);
//	tmp_node = rt_data->lights;
	current = 0;
//	while (tmp_node)
	while (current < rt_data->lights_num)
	{
		current_lamp = (rt_data->lights_arr) + current; //tmp_node;//
		add_coef(&light_coef, find_light_color(rt_data, current_lamp,
											closest_inter, r), 1);
		current++;
//		tmp_node = tmp_node->next;
	}
	final_color = fig_color_with_light(light_coef, closest_inter);
	return (final_color);
}

void		add_coef(t_channel *coef1, t_channel coef2, float coef)
{
	coef1->blue += coef2.blue * coef;
	coef1->green += coef2.green * coef;
	coef1->red += coef2.red * coef;
}

t_channel	find_light_color(t_rt *rt_data, t_light *current_lamp,
							t_intersect closest_inter, t_ray r)
{
	t_ray			light_ray;
	t_channel		lamp_coef;
	t_vector		normal;
	float			*cos_angle;

	ft_bzero(&lamp_coef, sizeof(t_channel));
	if (current_lamp->type == AMBIENT)
		add_coef(&lamp_coef, current_lamp->color, current_lamp->intensity);
	else
	{
		light_ray = find_light_ray(closest_inter.point, current_lamp);
		normal = choose_normal(closest_inter.fig, closest_inter.point);
		if (!is_shadows_here(light_ray, normal, r) ||
			!is_light_ray_cross_figure(rt_data, current_lamp->type, light_ray, closest_inter))
			return (lamp_coef);
		cos_angle = find_cos_angle(vect_mult_scalar(light_ray.direction, -1), closest_inter, normal, r);
		add_coef(&lamp_coef, current_lamp->color, cos_angle[0] *
												current_lamp->intensity);
		add_coef(&lamp_coef, (t_channel){1, 1, 1}, cos_angle[1] *
												current_lamp->intensity);
		free(cos_angle);
	}
	return (lamp_coef);
}

t_channel	fig_color_with_light(t_channel light_coef, t_intersect closest_inter)
{
	t_channel	color;

	color.red = fig_color_with_light_channel(closest_inter.fig->color.red,
											light_coef.red);
	color.green = fig_color_with_light_channel(closest_inter.fig->color.green,
											light_coef.green);
	color.blue = fig_color_with_light_channel(closest_inter.fig->color.blue,
											light_coef.blue);
	return (color);
}

t_ray		find_light_ray(t_vector origin, t_light *light)
{
	t_ray		light_ray;

	light_ray.origin = origin;
	if (light->type == SPOT)
		light_ray.direction = vect_diff(light->origin, origin);
	else if (light->type == DIRECT)
		light_ray.direction = vect_mult_scalar(light->direct, -1);
	light_ray.direction = normalize_vector(light_ray.direction);
	return (light_ray);
}
