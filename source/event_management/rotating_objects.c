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

//cl_float3	rotate_vector(cl_float3 vector, cl_float3 ang)
//{
//	cl_float3	vec;
//	float		tmp;
//
//	vec.y = vector.y * cosf(ang.x) - vector.z * sinf(ang.x);
//	vec.z = vector.y * sinf(ang.x) + vector.z * cosf(ang.x);
//
//	vec.x = vector.x * cosf(ang.y) + vec.z * sinf(ang.y);
//	vec.z = -vector.x * sinf(ang.y) + vec.z * cosf(ang.y);
//
//	tmp = vec.x;
//	vec.x = vec.x * cosf(ang.z) + vec.y * sinf(ang.z);
//	vec.y = -tmp * sinf(ang.z) + vec.y * cosf(ang.z);
//	return (vec);
//}

void		rotating_object(int keycode, t_rt *rt_data)
{
	double		angle;
	t_objects	*obj;
//	cl_float3	z_cam_basis;

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
		obj->basis = init_basis_after_rot(obj->init_basis, obj->angle_rot, VEC(0, 0, 1));

		if (!isinf(obj->cap[0].dist))
		{
//			z_cam_basis = matrix_mult_vect(count_inverse_matrix(obj->cap[0].basis),
//										   matrix_mult_vect(obj->cap[0].basis, obj->basis.b_z));

//            printf("basis: x = {%f, %f, %f}, y = {%f, %f, %f}, z = {%f, %f, %f}\n\n",
//               obj->cap[0].basis.b_x.x, obj->cap[0].basis.b_x.y, obj->cap[0].basis.b_x.z, obj->cap[0].basis.b_y.x,
//               obj->cap[0].basis.b_y.y, obj->cap[0].basis.b_y.z, obj->cap[0].basis.b_z.x, obj->cap[0].basis.b_z.y, obj->cap[0].basis.b_z.z);
//
//            printf("cap[0].basis = {%f, %f, %f}, basis.b_z = {%f, %f, %f}\n\n", z_cam_basis.x, z_cam_basis.y, z_cam_basis.z, obj->basis.b_z.x, obj->basis.b_z.y, obj->basis.b_z.z);
			obj->cap[0].basis = init_basis_after_rot(obj->cap[0].init_basis, obj->angle_rot, obj->basis.b_z);
		}
		if (!isinf(obj->cap[1].dist))
		{
//			z_cam_basis = matrix_mult_vect(count_inverse_matrix(obj->cap[1].init_basis), obj->basis.b_z);
			obj->cap[1].basis = init_basis_after_rot(obj->cap[1].init_basis, obj->angle_rot, obj->basis.b_z);
		}
        obj->cap[0].normal = obj->cap[0].basis.b_z;
        obj->cap[1].normal = obj->cap[1].basis.b_z;
//        printf("init: x = {%f, %f, %f}, y = {%f, %f, %f}, z = {%f, %f, %f}\n",
//               obj->cap[0].init_basis.b_x.x, obj->cap[0].init_basis.b_x.y, obj->cap[0].init_basis.b_x.z, obj->cap[0].init_basis.b_y.x,
//               obj->cap[0].init_basis.b_y.y, obj->cap[0].init_basis.b_y.z, obj->cap[0].init_basis.b_z.x, obj->cap[0].init_basis.b_z.y, obj->cap[0].init_basis.b_z.z);
//        printf("angle: x = %f, y = %f, z = %f\n", obj->angle_rot.x, obj->angle_rot.y, obj->angle_rot.z);
//
//        printf("basis: x = {%f, %f, %f}, y = {%f, %f, %f}, z = {%f, %f, %f}\n\n",
//               obj->cap[0].basis.b_x.x, obj->cap[0].basis.b_x.y, obj->cap[0].basis.b_x.z, obj->cap[0].basis.b_y.x,
//               obj->cap[0].basis.b_y.y, obj->cap[0].basis.b_y.z, obj->cap[0].basis.b_z.x, obj->cap[0].basis.b_z.y, obj->cap[0].
//                        basis.b_z.z);
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
