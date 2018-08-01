/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotating_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:48:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/01 22:09:38 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "../../includes/rt_functions.h"

void		if_isinf(t_objects *obj)
{
	if (!isinf(obj->cap[0].dist))
		obj->cap[0].basis =
init_basis_after_rot(obj->cap[0].init_basis, obj->angle_rot, obj->basis.b_z);
	if (!isinf(obj->cap[1].dist))
		obj->cap[1].basis =
init_basis_after_rot(obj->cap[1].init_basis, obj->angle_rot, obj->basis.b_z);
}

void		rotating_object(int keycode, t_rt *rt_data)
{
	double		angle;
	t_objects	*obj;

	angle = (keycode == SDLK_UP || keycode == SDLK_RIGHT ||
			keycode == SDLK_PAGEDOWN) ? ANGLE : -ANGLE;
	obj = find_object(rt_data);
	if (obj == NULL)
		rotating_camera(keycode, rt_data);
	else
	{
		if (keycode == SDLK_UP || keycode == SDLK_DOWN)
			obj->angle_rot.x += angle;
		else if (keycode == SDLK_RIGHT || keycode == SDLK_LEFT)
			obj->angle_rot.y -= angle;
		else
			obj->angle_rot.z += angle;
		obj->basis = init_basis_after_rot(obj->init_basis, obj->angle_rot,
		VEC(0, 0, 1));
		if_isinf(obj);
		obj->cap[0].normal = obj->cap[0].basis.b_z;
		obj->cap[1].normal = obj->cap[1].basis.b_z;
	}
}

t_objects	*find_object(t_rt *rt_data)
{
	int			current;

	current = 0;
	while (current < rt_data->cl_data.num_of_objects)
	{
		if (rt_data->objects_arr[current].is_cartoon == TRUE)
			return (&(rt_data->objects_arr[current]));
		current++;
	}
	return (NULL);
}
