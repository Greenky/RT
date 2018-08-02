/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object_and_light.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 19:33:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/02 11:51:38 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void		add_normal(t_objects *obj)
{
	cl_float3	v0v1;
	cl_float3	v0v2;

	v0v1 = vect_diff(obj->v1, obj->v0);
	v0v2 = vect_diff(obj->v2, obj->v0);
	obj->basis.b_z = vect_cross_product(v0v2, v0v1);
	obj->basis.b_z = normalize_vector(obj->basis.b_z);
}

void		add_obj_to_list(t_rt *rt_data, t_objects *object)
{
	t_objects	*step;

	if (object->type == TRIANGLE)
		add_normal(object);
	create_coord_system(&(object->basis), &(object->init_basis),
						&(object->angle_rot));
	object->next = NULL;
	step = rt_data->objects;
	if (step)
	{
		while (step->next)
			step = step->next;
		step->next = object;
	}
	else
		rt_data->objects = object;
}

void		add_light(t_rt *rt_data, t_light *light)
{
	t_light *step;

	light->next = NULL;
	step = rt_data->lights;
	if (step)
	{
		while (step->next)
			step = step->next;
		step->next = light;
	}
	else
		rt_data->lights = light;
}
