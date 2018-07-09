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

#include "../inc/rtv1.h"

uint32_t	find_color(t_scene_data *scene, t_intersect closest_inter, t_ray r)
{
	t_list		*tmp_node;
	t_light		*current_lamp;
	t_channel	light_coef;

	ft_bzero(&light_coef, sizeof(t_channel));
	tmp_node = scene->lights;
	while (tmp_node != NULL)
	{
		current_lamp = (t_light*)tmp_node->content;
		add_coef(&light_coef, find_lamp_coef(scene, current_lamp,
		closest_inter, r), 1);
		tmp_node = tmp_node->next;
	}
	return (find_color_hex(light_coef, closest_inter));
}

void		add_coef(t_channel *coef1, t_channel coef2, float coef)
{
	coef1->blue += coef2.blue * coef;
	coef1->green += coef2.green * coef;
	coef1->red += coef2.red * coef;
}

t_channel	find_lamp_coef(t_scene_data *scene, t_light *current_lamp,
			t_intersect closest_inter, t_ray r)
{
	t_ray			light_ray;
	t_channel		lamp_coef;
	t_vector		normal;
	float			*cos_angle;

	ft_bzero(&lamp_coef, sizeof(t_channel));
	if (current_lamp->type == AMBIENT)
		add_coef(&lamp_coef, current_lamp->color, current_lamp->brightness);
	else
	{
		light_ray = find_light_ray(current_lamp->origin, closest_inter.point);
		normal = closest_inter.fig->
			find_normal_to_figure(closest_inter.fig, closest_inter.point);
		if (!is_shadows_here(light_ray, normal, r) ||
			!is_figure_first_inter_by_light(scene, light_ray, closest_inter))
			return (lamp_coef);
		cos_angle = find_cos_angle(light_ray, closest_inter, normal, r);
		add_coef(&lamp_coef, current_lamp->color, cos_angle[0] *
				current_lamp->brightness);
		add_coef(&lamp_coef, (t_channel){1, 1, 1}, cos_angle[1] *
				current_lamp->brightness);
		free(cos_angle);
	}
	return (lamp_coef);
}

t_ray		find_light_ray(t_vector origin, t_vector end)
{
	t_ray		light_ray;

	light_ray.origin = origin;
	light_ray.direction = vect_diff(end, origin);
	return (light_ray);
}
