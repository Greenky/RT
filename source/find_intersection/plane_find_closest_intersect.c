/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_find_closest_intersect.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:33:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:58:59 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void	plane_find_closest_intersect(t_ray r, t_intersect *inter)
{
	cl_float3	origin_diff;
	float		n_mult_dir;

	n_mult_dir = vect_scalar_mult(inter->fig->basis.b_z, r.direction);
	if (n_mult_dir == 0)
		inter->distance = INFINITY;
	else
	{
		origin_diff = vect_diff(inter->fig->origin, r.origin);
		inter->distance =
				(vect_scalar_mult(inter->fig->basis.b_z, origin_diff)) /
				n_mult_dir;
		if (inter->distance < 0)
			inter->distance = INFINITY;
		if (inter->distance != INFINITY)
		{
			inter->point = vect_sum(r.origin,
									vect_mult_scalar(r.direction,
													inter->distance));
			inter->normal = choose_normal(*inter->fig, inter->point);
		}
	}
}
