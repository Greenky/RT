/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_find_closest_intersect.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 12:52:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:59:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	cone_find_closest_intersect(t_ray r, t_intersect *inter)
{
	float	discriminant;
	float	t[2];
	float	coefficient[3];
	t_ray	r_cone_sys;

	r_cone_sys.origin = vect_diff(r.origin, inter->fig->origin);
	r_cone_sys.origin =
	matrice_mult_vect(count_inverse_matrix(inter->fig->basis),
						r_cone_sys.origin);
	r_cone_sys.direction =
	matrice_mult_vect(count_inverse_matrix(inter->fig->basis), r.direction);
	discriminant = find_cone_discriminant(r_cone_sys, coefficient,
					inter->fig->radius_or_cone_coef);
	if (!find_the_root(coefficient, discriminant, t))
		inter->distance = INFINITY;
	else
	{
		inter->point = vect_sum(r.origin, vect_mult(r.direction, t[0]));
		inter->distance = t[0];
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
