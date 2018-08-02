/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_find_closest_intersect.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 11:46:06 by vmazurok          #+#    #+#             */
/*   Updated: 2018/08/02 11:47:09 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int		check_position(cl_float3 v_start, cl_float3 v_end, t_intersect *inter)
{
	cl_float3	perpendicular;
	cl_float3	edge_vec;
	cl_float3	vec_to_intersect;

	edge_vec = vect_diff(v_end, v_start);
	vec_to_intersect = vect_diff(inter->point, v_start);
	perpendicular = vect_cross_product(vec_to_intersect, edge_vec);
	if (vect_scalar_mult(inter->fig->basis.b_z, perpendicular) < 0)
	{
		inter->distance = INFINITY;
		return (FALSE);
	}
	return (TRUE);
}

void	triangle_find_closest_intersect(t_ray r, t_intersect *inter)
{
	inter->fig->origin = inter->fig->v0;
	plane_find_closest_intersect(r, inter);
	if (isinf(inter->distance))
		return ;
	if (!check_position(inter->fig->v0, inter->fig->v1, inter))
		return ;
	if (!check_position(inter->fig->v1, inter->fig->v2, inter))
		return ;
	if (!check_position(inter->fig->v2, inter->fig->v0, inter))
		return ;
}
