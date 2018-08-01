/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures_normals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 21:57:07 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/31 21:05:22 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

cl_float3	find_normal_to_sphere(t_objects sphere, cl_float3 inter)
{
	cl_float3		normal_to_sphere;
	cl_float3		normal_to_sphere_unit;

	normal_to_sphere = vect_diff(inter, sphere.origin);
	normal_to_sphere_unit =
			vect_mult_scalar(normalize_vector(normal_to_sphere), -1);
	return (normal_to_sphere_unit);
}

cl_float3	find_normal_to_cone(t_objects cone, cl_float3 inter)
{
	cl_float3		normal;
	cl_float3		normal_unit;
	float			height;
	cl_float3		inter_orig;

	inter_orig = vect_diff(cone.origin, inter);
	if (inter_orig.x == 0 && inter_orig.y == 0 && inter_orig.z == 0)
		return (VEC(0, 0, 1));
	height = -vect_scalar_mult(inter_orig, inter_orig) /
			vect_scalar_mult(cone.basis.b_z, inter_orig);
	normal = vect_diff(vect_sum(cone.origin,
						vect_mult_scalar(cone.basis.b_z, height)), inter);
	normal_unit = normalize_vector(normal);
	return (normal_unit);
}

cl_float3	find_normal_to_plane(t_objects plane, cl_float3 inter)
{
	(void)inter;
	return (vect_mult_scalar(plane.basis.b_z, -1));
}

cl_float3	find_normal_to_cylinder(t_objects cyl, cl_float3 inter)
{
	cl_float3		normal;
	cl_float3		normal_unit;
	float			t;
	cl_float3		orig_inter;

	orig_inter = vect_diff(inter, cyl.origin);
	t = vect_scalar_mult(orig_inter, cyl.basis.b_z) /
		vect_scalar_mult(cyl.basis.b_z, cyl.basis.b_z);
	normal = vect_diff(vect_sum(cyl.origin,
						vect_mult_scalar(cyl.basis.b_z, t)), inter);
	normal_unit = normalize_vector(normal);
	return (normal_unit);
}

cl_float3	find_normal_to_ellipsoid(t_objects ellipsoid, cl_float3 inter)
{
	cl_float3	normal_to_ellipsoid;
	cl_float3	inter_in_ell_sys;

	inter_in_ell_sys = vect_diff(inter, ellipsoid.origin);
	inter_in_ell_sys = matrix_mult_vect(count_inverse_matrix(ellipsoid.basis),
	inter_in_ell_sys);
	normal_to_ellipsoid.x = inter_in_ell_sys.x * 2
		/ find_square(ellipsoid.axis_dimensions.x * ellipsoid.radius);
	normal_to_ellipsoid.y = inter_in_ell_sys.y * 2
		/ find_square(ellipsoid.axis_dimensions.y * ellipsoid.radius);
	normal_to_ellipsoid.z = inter_in_ell_sys.z * 2
		/ find_square(ellipsoid.axis_dimensions.z * ellipsoid.radius);
	normal_to_ellipsoid = matrix_mult_vect(ellipsoid.basis,
	normal_to_ellipsoid);
	normal_to_ellipsoid =
		vect_mult_scalar(normalize_vector(normal_to_ellipsoid), -1);
	return (normal_to_ellipsoid);
}
