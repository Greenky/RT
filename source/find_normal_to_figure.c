/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_normal_to_figure.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:44:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/13 20:09:28 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

cl_float3	choose_normal(t_objects *figure, cl_float3 inter)
{
	if (figure->type == SPHERE)
		return (find_normal_to_sphere(figure, inter));
	else if (figure->type == CYLINDER)
		return (find_normal_to_cylinder(figure, inter));
	else if (figure->type == CONE)
		return (find_normal_to_cone(figure, inter));
	else if (figure->type == PLANE)
		return (find_normal_to_plane(figure, inter));
	else
		return VEC(1, 1, 1);//(cl_float3){1,1,1}; // idk, let it be
}

cl_float3	find_normal_to_sphere(t_objects *sphere, cl_float3 inter)
{
	cl_float3		normal_to_sphere;
	cl_float3		normal_to_sphere_unit;

	normal_to_sphere = vect_diff(inter, sphere->origin);
	normal_to_sphere_unit = vect_mult(normalize_vector(normal_to_sphere), -1);
	return (normal_to_sphere_unit);
}

cl_float3	find_normal_to_cone(t_objects *cone, cl_float3 inter)
{
	cl_float3		normal;
	cl_float3		normal_unit;
	float			height;
	cl_float3		inter_orig;

	inter_orig = vect_diff(cone->origin, inter);
	height = -vect_scalar_mult(inter_orig, inter_orig) /
		vect_scalar_mult(cone->basis.b_z, inter_orig);
	normal = vect_diff(vect_sum(cone->origin, vect_mult(cone->basis.b_z,
				height)), inter);
	normal_unit = normalize_vector(normal);
	return (normal_unit);
}

cl_float3	find_normal_to_plane(t_objects *plane, cl_float3 inter)
{
	(void)inter;
	return (vect_mult(plane->basis.b_z, -1));
}

cl_float3	find_normal_to_cylinder(t_objects *cyl, cl_float3 inter)
{
	cl_float3		normal;
	cl_float3		normal_unit;
	float			t;
	cl_float3		orig_inter;

	orig_inter = vect_diff(inter, cyl->origin);
	t = vect_scalar_mult(orig_inter, cyl->basis.b_z) /
	vect_scalar_mult(cyl->basis.b_z, cyl->basis.b_z);
	normal = vect_diff(vect_sum(cyl->origin,
				vect_mult(cyl->basis.b_z, t)), inter);
	normal_unit = normalize_vector(normal);
	return (normal_unit);
}
