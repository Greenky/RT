/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_find_closest_intersect.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 19:23:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:59:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	sphere_find_closest_intersect(t_ray r, t_intersect *inter)
{
	float	discriminant;
	float	t[2];
	float	coefficient[3];

	discriminant = find_sphere_discriminant(r, inter->fig, coefficient);
	if (!find_the_root(coefficient, discriminant, t))
		inter->distance = INFINITY;
	else
	{
		inter->point = vect_sum(r.origin, vect_mult(r.direction, t[0]));
		inter->distance = t[0];
	}
}

float	find_sphere_discriminant(t_ray r, t_figure *fig, float coefficient[3])
{
	float		discriminant;
	t_vector	cam_origin;

	cam_origin = vect_diff(r.origin, fig->origin);
	coefficient[A] = vect_scalar_mult(r.direction, r.direction);
	coefficient[B] = vect_scalar_mult(r.direction, cam_origin);
	coefficient[C] = vect_scalar_mult(cam_origin, cam_origin)
					- find_square(fig->radius_or_cone_coef);
	discriminant = find_square(coefficient[B]) -
					coefficient[A] * coefficient[C];
	return (discriminant);
}

int		find_the_root(float coefficient[3], float discriminant, float t[2])
{
	float	square_d;

	if (discriminant < 0)
		return (FALSE);
	else if (discriminant == 0)
	{
		t[0] = -coefficient[B] / coefficient[A];
		t[1] = -1;
	}
	else
	{
		square_d = sqrtf(discriminant);
		t[0] = (-coefficient[B] + square_d) / coefficient[A];
		t[1] = (-coefficient[B] - square_d) / coefficient[A];
	}
	if (t[0] < 0 && t[1] < 0)
		return (FALSE);
	if ((t[1] < t[0] && t[1] >= 0) || t[0] < 0)
		t[0] = t[1];
	return (TRUE);
}
