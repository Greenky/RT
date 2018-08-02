/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 21:50:36 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 21:50:38 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void			fill_object(t_rt *rt_data, t_objects *step_obj, int len)
{
	rt_data->objects_arr[len].type = step_obj->type;
	rt_data->objects_arr[len].color = step_obj->color;
	rt_data->objects_arr[len].origin = step_obj->origin;
	rt_data->objects_arr[len].normal = step_obj->normal;
	rt_data->objects_arr[len].radius = step_obj->radius;
	rt_data->objects_arr[len].angle_coef = step_obj->angle_coef;
	rt_data->objects_arr[len].basis = step_obj->basis;
	rt_data->objects_arr[len].mirror_coef = step_obj->mirror_coef;
	rt_data->objects_arr[len].transperent_coef = step_obj->transperent_coef;
	rt_data->objects_arr[len].axis_dimensions = step_obj->axis_dimensions;
	rt_data->objects_arr[len].bling_phong = step_obj->bling_phong;
	rt_data->objects_arr[len].texture_repeat = step_obj->texture_repeat;
	rt_data->objects_arr[len].texture_index = step_obj->texture_index;
	rt_data->objects_arr[len].cap[0] = step_obj->cap[0];
	rt_data->objects_arr[len].cap[1] = step_obj->cap[1];
	rt_data->objects_arr[len].is_cartoon = 0;
	rt_data->objects_arr[len].angle_rot = step_obj->angle_rot;
	rt_data->objects_arr[len].init_basis = step_obj->init_basis;
	rt_data->objects_arr[len].v0 = step_obj->v0;
	rt_data->objects_arr[len].v1 = step_obj->v1;
	rt_data->objects_arr[len].v2 = step_obj->v2;
	rt_data->objects_arr[len].next = NULL;
}

void			fill_light(t_rt *rt_data, t_light *step_light, int len)
{
	rt_data->lights_arr[len].origin = step_light->origin;
	rt_data->lights_arr[len].color = step_light->color;
	rt_data->lights_arr[len].type = step_light->type;
	rt_data->lights_arr[len].direct = step_light->direct;
	rt_data->lights_arr[len].intensity = step_light->intensity;
	rt_data->lights_arr[len].next = NULL;
}

void			init_objects_array(t_rt *rt_data)
{
	t_objects	*step_obj;
	int			len;

	len = 0;
	step_obj = rt_data->objects;
	while (step_obj)
	{
		len++;
		step_obj = step_obj->next;
	}
	rt_data->cl_data.num_of_objects = len;
	rt_data->objects_arr = (t_objects *)malloc(sizeof(t_objects) * len);
	len = -1;
	step_obj = rt_data->objects;
	while (++len < rt_data->cl_data.num_of_objects)
	{
		fill_object(rt_data, step_obj, len);
		step_obj = step_obj->next;
	}
}

void			init_lights_array(t_rt *rt_data)
{
	t_light		*step_light;
	int			len;

	len = 0;
	step_light = rt_data->lights;
	while (step_light)
	{
		len++;
		step_light = step_light->next;
	}
	rt_data->cl_data.num_of_lights = len;
	rt_data->lights_arr = (t_light *)malloc(sizeof(t_light) * len);
	len = -1;
	step_light = rt_data->lights;
	while (++len < rt_data->cl_data.num_of_lights)
	{
		fill_light(rt_data, step_light, len);
		step_light = step_light->next;
	}
}

void			init_arrays(t_rt *rt_data)
{
	init_objects_array(rt_data);
	init_lights_array(rt_data);
	freesher(rt_data->lights, rt_data->objects);
	rt_data->lights = NULL;
	rt_data->objects = NULL;
}
