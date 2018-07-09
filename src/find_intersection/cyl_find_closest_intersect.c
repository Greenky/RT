/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_find_closest_intersect.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 19:59:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:59:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	cyl_find_closest_intersect(t_ray r, t_intersect *inter)
{
	float	discriminant;
	float	t[2];
	float	coefficient[3];
	t_ray	r_cyl_sys;

	r_cyl_sys.origin = vect_diff(r.origin, inter->fig->origin);
	r_cyl_sys.origin =
	matrice_mult_vect(count_inverse_matrix(inter->fig->basis),
						r_cyl_sys.origin);
	r_cyl_sys.direction =
	matrice_mult_vect(count_inverse_matrix(inter->fig->basis), r.direction);
	discriminant = find_cyl_discriminant(r_cyl_sys,
					inter->fig->radius_or_cone_coef, coefficient);
	if (!find_the_root(coefficient, discriminant, t))
		inter->distance = INFINITY;
	else
	{
		inter->point = vect_sum(r.origin, vect_mult(r.direction, t[0]));
		inter->distance = t[0];
	}
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
