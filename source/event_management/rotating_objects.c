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

void		init_obj_basis_after_rot(t_coord_sys init_basis_obj,
									cl_float3 angle_rot, t_objects *obj)
{
	t_coord_sys		new_basis_obj;

	new_basis_obj = matrix_mult_matrix(init_basis_obj,
						rot_matrix_about_the_axis(angle_rot.z, VEC(0, 0, 1)));
	init_cap_basis_after_rot(new_basis_obj, obj, obj->cap[0].angle_rot, AXIS_Z);
	new_basis_obj = matrix_mult_matrix(new_basis_obj,
						rot_matrix_about_the_axis(angle_rot.y, VEC(0, 1, 0)));
	init_cap_basis_after_rot(new_basis_obj, obj, obj->cap[0].angle_rot, AXIS_Y);
	new_basis_obj = matrix_mult_matrix(new_basis_obj,
						(rot_matrix_about_the_axis(angle_rot.x, VEC(1, 0, 0))));
	init_cap_basis_after_rot(new_basis_obj, obj, obj->cap[0].angle_rot, AXIS_X);
	obj->basis = new_basis_obj;
}

void		check_caps_normals(t_objects *obj)
{
	float	cos;

	if (!isinf(obj->cap[0].dist))
	{
		cos = vect_scalar_mult(obj->cap[0].init_basis.b_z, obj->init_basis.b_z);
		if (cos < 0)
			obj->cap[0].init_basis.b_z =
					vect_mult_scalar(obj->cap[0].init_basis.b_z, -1);
		obj->cap[0].angle_rot = obj->angle_rot;
		if (obj->init_basis.b_z.y < 0)
			obj->cap[0].angle_rot = vect_mult_scalar(obj->angle_rot, -1);
	}
	if (!isinf(obj->cap[1].dist))
	{
		cos = vect_scalar_mult(obj->cap[1].init_basis.b_z, obj->init_basis.b_z);
		if (cos < 0)
			obj->cap[1].init_basis.b_z =
					vect_mult_scalar(obj->cap[1].init_basis.b_z, -1);
	}
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
		if (!isinf(obj->cap[0].dist) || !isinf(obj->cap[1].dist))
			check_caps_normals(obj);
		init_obj_basis_after_rot(obj->init_basis, obj->angle_rot, obj);
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
