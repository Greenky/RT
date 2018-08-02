/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_find_limited.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 19:59:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/31 21:41:55 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int		handle_caps_overlap(float cap_norm_inter[2][2], t_objects obj,
							t_intersect *inter)
{
	if (cap_norm_inter[0][0] > cap_norm_inter[1][0])
	{
		inter->fig->basis.b_z = obj.cap[0].normal;
		inter->fig->origin = vect_sum(obj.origin,
		vect_mult_scalar(obj.basis.b_z, obj.cap[0].dist));
	}
	else if (cap_norm_inter[0][0] < cap_norm_inter[1][0])
	{
		inter->fig->basis.b_z = obj.cap[1].normal;
		inter->fig->origin = vect_sum(obj.origin,
		vect_mult_scalar(obj.basis.b_z, obj.cap[1].dist));
	}
	else
	{
		free(inter->fig);
		return (FALSE);
	}
	return (TRUE);
}

int		hit_top_cap(float cap_norm_inter[2][2])
{
	return ((cap_norm_inter[0][0] >= 0 && cap_norm_inter[0][1] < 0 &&
			(cap_norm_inter[1][1] < 0 || (cap_norm_inter[1][0] < 0 &&
			cap_norm_inter[1][1] >= 0))));
}

int		hit_bottom_cap(float cap_norm_inter[2][2])
{
	return (cap_norm_inter[1][0] >= 0 && cap_norm_inter[1][1] < 0 &&
			(cap_norm_inter[0][1] < 0 || (cap_norm_inter[0][0] < 0 &&
			cap_norm_inter[0][1] >= 0)));
}

int		find_cap_intersection(float cap_norm_inter[2][2], t_objects obj,
								t_intersect *inter)
{
	int	ret;

	ret = TRUE;
	if (cap_norm_inter[0][0] >= 0 && cap_norm_inter[1][0] >= 0
		&& cap_norm_inter[0][1] < 0 && cap_norm_inter[1][1] < 0)
		return (handle_caps_overlap(cap_norm_inter, obj, inter));
	if (hit_top_cap(cap_norm_inter))
	{
		inter->fig->basis.b_z = obj.cap[0].normal;
		inter->fig->origin = vect_sum(obj.origin,
		vect_mult_scalar(obj.basis.b_z, obj.cap[0].dist));
	}
	else if (hit_bottom_cap(cap_norm_inter))
	{
		inter->fig->basis.b_z = obj.cap[1].normal;
		inter->fig->origin = vect_sum(obj.origin,
		vect_mult_scalar(obj.basis.b_z, obj.cap[1].dist));
	}
	else
	{
		free(inter->fig);
		ret = FALSE;
	}
	return (ret);
}

float	limit_cylinder(t_objects cyl, t_ray r, t_intersect *inter, float t[2])
{
	float		cap_norm_inter[2][2];
	t_intersect	tmp_inter;

	data_validation(&cyl);
	find_norm_intersections(r, cyl, t, cap_norm_inter);
	if (isinf(cyl.cap[1].dist))
	{
		cap_norm_inter[1][0] = -INFINITY;
		cap_norm_inter[1][1] = -INFINITY;
	}
	if (isinf(cyl.cap[0].dist))
	{
		cap_norm_inter[0][0] = -INFINITY;
		cap_norm_inter[0][1] = -INFINITY;
	}
	if (main_object_is_hit(inter, r, t, cap_norm_inter))
		return (t[0]);
	tmp_inter.fig = (t_objects *)malloc(sizeof(t_objects));
	if (!find_cap_intersection(cap_norm_inter, cyl, &tmp_inter))
		return (INFINITY);
	inter->normal = find_normal_to_plane(*tmp_inter.fig, tmp_inter.point);
	plane_find_closest_intersect(r, &tmp_inter);
	free(tmp_inter.fig);
	return (tmp_inter.distance);
}
