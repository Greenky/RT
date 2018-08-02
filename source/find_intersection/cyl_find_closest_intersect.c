/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_find_closest_intersect.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 19:59:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/31 21:44:29 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void	cyl_find_closest_intersect(t_ray r, t_intersect *inter)
{
	float	discriminant;
	float	t[2];
	float	coefficient[3];
	t_ray	r_cyl_sys;

	r_cyl_sys.origin = vect_diff(r.origin, inter->fig->origin);
	r_cyl_sys.origin =
			matrix_mult_vect(count_inverse_matrix(inter->fig->basis),
							r_cyl_sys.origin);
	r_cyl_sys.direction =
			matrix_mult_vect(count_inverse_matrix(inter->fig->basis),
							r.direction);
	discriminant = find_cyl_discriminant(r_cyl_sys,
										inter->fig->radius, coefficient);
	if (!find_the_root(coefficient, discriminant, t))
		inter->distance = INFINITY;
	else
	{
		inter->distance = (!isinf(inter->fig->cap[0].dist) || !isinf(
inter->fig->cap[1].dist)) ? limit_cylinder(*inter->fig, r, inter, t) : t[0];
		inter->point = vect_sum(r.origin,
		vect_mult_scalar(r.direction, inter->distance));
		if (isinf(inter->fig->cap[0].dist) && isinf(inter->fig->cap[1].dist))
			inter->normal = choose_normal(*inter->fig, inter->point);
	}
}

void	data_validation(t_objects *obj)
{
	float		tmp_cap;
	cl_float3	tmp_norm;

	if (obj->cap[0].dist > obj->cap[1].dist && !isinf(obj->cap[1].dist))
	{
		tmp_cap = obj->cap[0].dist;
		tmp_norm = obj->cap[0].normal;
		obj->cap[0].dist = obj->cap[1].dist;
		obj->cap[0].normal = obj->cap[1].normal;
		obj->cap[1].dist = tmp_cap;
		obj->cap[1].normal = tmp_norm;
	}
	if (obj->cap[0].dist == obj->cap[1].dist &&
			!isinf(obj->cap[0].dist) && !isinf(obj->cap[1].dist))
		obj->cap[0].dist -= 0.1;
	obj->cap[0].normal =
			(vect_scalar_mult(obj->cap[0].normal, obj->basis.b_z) < 0) ?
			(obj->cap[0].normal) : (vect_mult_scalar(obj->cap[0].normal, -1));
	obj->cap[1].normal =
			(vect_scalar_mult(obj->cap[1].normal, obj->basis.b_z) >= 0) ?
			(obj->cap[1].normal) : (vect_mult_scalar(obj->cap[1].normal, -1));
	obj->cap[0].normal = normalize_vector(obj->cap[0].normal);
	obj->cap[1].normal = normalize_vector(obj->cap[1].normal);
}

void	find_norm_intersections(t_ray r, t_objects obj, float t[2],
								float cap_norm_inter[2][2])
{
	cl_float3	co[2];

	co[0] = vect_diff(r.origin, vect_sum(obj.origin,
						vect_mult_scalar(obj.basis.b_z, obj.cap[0].dist)));
	co[1] = vect_diff(r.origin, vect_sum(obj.origin,
						vect_mult_scalar(obj.basis.b_z, obj.cap[1].dist)));
	cap_norm_inter[0][0] = vect_scalar_mult(r.direction, obj.cap[0].normal) *
						t[0] + vect_scalar_mult(co[0], obj.cap[0].normal);
	cap_norm_inter[0][1] = vect_scalar_mult(r.direction, obj.cap[0].normal) *
						t[1] + vect_scalar_mult(co[0], obj.cap[0].normal);
	cap_norm_inter[1][0] = vect_scalar_mult(r.direction, obj.cap[1].normal) *
						t[0] + vect_scalar_mult(co[1], obj.cap[1].normal);
	cap_norm_inter[1][1] = vect_scalar_mult(r.direction, obj.cap[1].normal) *
						t[1] + vect_scalar_mult(co[1], obj.cap[1].normal);
}

int		main_object_is_hit(t_intersect *inter, t_ray r, float t[2],
							float cap_norm_inter[2][2])
{
	if (cap_norm_inter[0][0] < 0 && cap_norm_inter[1][0] < 0)
	{
		inter->point = vect_sum(r.origin, vect_mult_scalar(r.direction, t[0]));
		inter->normal = choose_normal(*inter->fig, inter->point);
		return (TRUE);
	}
	return (FALSE);
}

float	find_cyl_discriminant(t_ray r, float radius, float *coefficient)
{
	float	discriminant;

	coefficient[A] = find_square(r.direction.x) + find_square(r.direction.y);
	coefficient[B] = r.origin.x * r.direction.x + r.origin.y * r.direction.y;
	coefficient[C] = find_square(r.origin.x) + find_square(r.origin.y) -
					find_square(radius);
	discriminant = find_square(coefficient[B]) -
					coefficient[A] * coefficient[C];
	return (discriminant);
}
