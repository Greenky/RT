/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_find_closest_intersect.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 12:52:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/31 21:08:48 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

float	limit_cone(t_objects con, t_ray r, t_intersect *inter, float t[2])
{
	float		cap_norm_inter[2][2];
	t_intersect	tmp_inter;

	data_validation(&con);
	find_norm_intersections(r, con, t, cap_norm_inter);
	if (isinf(con.cap[1].dist))
	{
		cap_norm_inter[1][0] = -INFINITY;
		cap_norm_inter[1][1] = -INFINITY;
	}
	if (isinf(con.cap[0].dist))
	{
		cap_norm_inter[0][0] = -INFINITY;
		cap_norm_inter[0][1] = -INFINITY;
	}
	if (main_object_is_hit(inter, r, t, cap_norm_inter))
		return (t[0]);
	tmp_inter.fig = (t_objects *)malloc(sizeof(t_objects));
	if (!find_cap_intersection(cap_norm_inter, con, &tmp_inter))
		return (INFINITY);
	inter->normal = find_normal_to_plane(*tmp_inter.fig, tmp_inter.point);
	plane_find_closest_intersect(r, &tmp_inter);
	free(tmp_inter.fig);
	return (tmp_inter.distance);
}

void	cone_find_closest_intersect(t_ray r, t_intersect *inter)
{
	float	discriminant;
	float	t[2];
	float	coefficient[3];
	t_ray	r_cone_sys;

	r_cone_sys.origin = vect_diff(r.origin, inter->fig->origin);
	r_cone_sys.origin = matrix_mult_vect(count_inverse_matrix(
	inter->fig->basis), r_cone_sys.origin);
	r_cone_sys.direction = matrix_mult_vect(count_inverse_matrix(
	inter->fig->basis), r.direction);
	discriminant = find_cone_discriminant(r_cone_sys, coefficient,
	inter->fig->angle_coef);
	if (!find_the_root(coefficient, discriminant, t))
		inter->distance = INFINITY;
	else
	{
		inter->distance = (!isinf(inter->fig->cap[0].dist) || !isinf(
	inter->fig->cap[1].dist)) ? limit_cone(*inter->fig, r, inter, t) : t[0];
		inter->point =
			vect_sum(r.origin, vect_mult_scalar(r.direction, inter->distance));
		if (isinf(inter->fig->cap[0].dist) && isinf(inter->fig->cap[1].dist))
			inter->normal = choose_normal(*inter->fig, inter->point);
	}
}

float	find_cone_discriminant(t_ray r, float *coefficient, float coef)
{
	float	discriminant;

	coef = find_square(coef);
	coefficient[A] = find_square(r.direction.x) + find_square(r.direction.y) -
					find_square(r.direction.z) * coef;
	coefficient[B] = r.origin.x * r.direction.x + r.origin.y * r.direction.y -
					r.origin.z * r.direction.z * coef;
	coefficient[C] = find_square(r.origin.x) + find_square(r.origin.y) -
					find_square(r.origin.z) * coef;
	discriminant = find_square(coefficient[B]) -
					coefficient[A] * coefficient[C];
	return (discriminant);
}
