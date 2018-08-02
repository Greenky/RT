/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotating_and_shift_camera.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 18:01:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/01 22:15:28 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void		rotating_camera(int keycode, t_rt *rt_data)
{
	double		angle;

	angle = (keycode == SDLK_UP || keycode == SDLK_RIGHT ||
			keycode == SDLK_PAGEDOWN) ? ANGLE : -ANGLE;
	if (keycode == SDLK_UP || keycode == SDLK_DOWN)
		rt_data->cl_data.camera.angle_rot.x += angle;
	else if (keycode == SDLK_RIGHT || keycode == SDLK_LEFT)
		rt_data->cl_data.camera.angle_rot.y -= angle;
	else
		rt_data->cl_data.camera.angle_rot.z += angle;
	rt_data->cl_data.camera.basis =
			init_basis_after_rot(rt_data->cl_data.camera.initial_basis,
			rt_data->cl_data.camera.angle_rot);
}

t_coord_sys	init_basis_after_rot(t_coord_sys initial_basis, cl_float3 angle_rot)
{
	t_coord_sys		new_basis;

	new_basis = matrix_mult_matrix(initial_basis,
					rot_matrix_about_the_axis(angle_rot.z, VEC(0, 0, 1)));
	new_basis = matrix_mult_matrix(new_basis,
					rot_matrix_about_the_axis(angle_rot.y, VEC(0, 1, 0)));
	new_basis = matrix_mult_matrix(new_basis,
					(rot_matrix_about_the_axis(angle_rot.x, VEC(1, 0, 0))));
	return (new_basis);
}

t_coord_sys	rot_matrix_about_the_axis(float angle, cl_float3 axis)
{
	t_coord_sys rot_matrix;

	rot_matrix.b_x.x = cosf(angle) + (1 - cosf(angle)) * find_square(axis.x);
	rot_matrix.b_y.x = (1 - cosf(angle))
					* axis.x * axis.y - sinf(angle) * axis.z;
	rot_matrix.b_z.x = (1 - cosf(angle))
					* axis.x * axis.z + sinf(angle) * axis.y;
	rot_matrix.b_x.y = (1 - cosf(angle))
					* axis.y * axis.x + sinf(angle) * axis.z;
	rot_matrix.b_y.y = cosf(angle)
					+ (1 - cosf(angle)) * find_square(axis.y);
	rot_matrix.b_z.y = (1 - cosf(angle))
					* axis.y * axis.z - sinf(angle) * axis.x;
	rot_matrix.b_x.z = (1 - cosf(angle))
					* axis.z * axis.x - sinf(angle) * axis.y;
	rot_matrix.b_y.z = (1 - cosf(angle))
					* axis.z * axis.y + sinf(angle) * axis.x;
	rot_matrix.b_z.z = cosf(angle)
					+ (1 - cosf(angle)) * find_square(axis.z);
	return (rot_matrix);
}

void		manage_camera_origin(int keycode, t_rt *rt_data)
{
	if (keycode == SDLK_w)
		rt_data->cl_data.camera.origin =
			vect_diff(rt_data->cl_data.camera.origin,
			vect_mult_scalar(rt_data->cl_data.camera.basis.b_z, SHIFT_STEP));
	else if (keycode == SDLK_s)
		rt_data->cl_data.camera.origin =
			vect_sum(rt_data->cl_data.camera.origin,
			vect_mult_scalar(rt_data->cl_data.camera.basis.b_z, SHIFT_STEP));
	else if (keycode == SDLK_d)
		rt_data->cl_data.camera.origin =
			vect_sum(rt_data->cl_data.camera.origin,
			vect_mult_scalar(rt_data->cl_data.camera.basis.b_x, SHIFT_STEP));
	else if (keycode == SDLK_a)
		rt_data->cl_data.camera.origin =
			vect_diff(rt_data->cl_data.camera.origin,
			vect_mult_scalar(rt_data->cl_data.camera.basis.b_x, SHIFT_STEP));
}

void		reset_camera_settings(t_rt *rt_data)
{
	rt_data->cl_data.camera.basis = rt_data->cl_data.camera.initial_basis;
	rt_data->cl_data.camera.origin = VEC(0, 0, -20);
	rt_data->cl_data.camera.angle_rot = VEC(0, 0, 0);
}
