/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotating_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:48:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/29 16:48:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "../../includes/rt_functions.h"

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
			obj->angle_rot.y += angle;
		else if (keycode == SDLK_RIGHT || keycode == SDLK_LEFT)
			obj->angle_rot.x -= angle;
		else
			obj->angle_rot.z += angle;
		obj->basis = init_basis_after_rot(obj->initial_basis, obj->angle_rot);
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
