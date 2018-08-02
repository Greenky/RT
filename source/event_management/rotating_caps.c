/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotating_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:33:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/02 15:33:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "../../includes/rt_functions.h"

cl_float3	init_cap_axis(t_coord_sys new_basis_obj, t_objects *obj,
							int axis, int cup_num)
{
	cl_float3	new_axis;

	if (axis == AXIS_Z)
		new_axis =
			matrix_mult_vect(count_inverse_matrix(obj->cap[cup_num].init_basis),
								obj->init_basis.b_z);
	else if (axis == AXIS_Y)
		new_axis =
				matrix_mult_vect(count_inverse_matrix(obj->cap[cup_num].basis),
								new_basis_obj.b_y);
	else
		new_axis =
				matrix_mult_vect(count_inverse_matrix(obj->cap[cup_num].basis),
								new_basis_obj.b_x);
	return (new_axis);
}

void		init_cap_basis_after_rot
	(t_coord_sys new_basis_obj, t_objects *obj, cl_float3 angle_rot, int axis)
{
	cl_float3		new_axis;
	t_coord_sys		basisss;
	float			angle;

	if (axis == AXIS_Z)
		angle = angle_rot.z;
	else
		angle = (axis == AXIS_Y) ? angle_rot.y : angle_rot.x;
	if (!isinf(obj->cap[0].dist))
	{
		new_axis = init_cap_axis(new_basis_obj, obj, axis, 0);
		basisss = (axis == AXIS_Z) ? obj->cap[0].init_basis : obj->cap[0].basis;
		obj->cap[0].basis = matrix_mult_matrix(basisss,
									rot_matrix_about_the_axis(angle, new_axis));
	}
	if (!isinf(obj->cap[1].dist))
	{
		new_axis = init_cap_axis(new_basis_obj, obj, axis, 1);
		basisss = (axis == AXIS_Z) ? obj->cap[1].init_basis : obj->cap[1].basis;
		obj->cap[1].basis = matrix_mult_matrix(basisss,
									rot_matrix_about_the_axis(angle, new_axis));
	}
}
