/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_find_closest_intersec.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:37:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/23 17:37:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void	ellipsoid_find_closest_intersect(t_ray ray, t_intersect *inter)
{
	t_ray		imaginary_sphere_ray;

	imaginary_sphere_ray = find_ray_for_imaginary_sphere(ray, inter->fig);
	sphere_find_closest_intersect(imaginary_sphere_ray, inter);
	if (inter->distance == INFINITY)
		return ;
	else
	{
		inter->point = vect_diff(inter->point, inter->fig->origin);
		inter->point =
				matrix_mult_vect(count_inverse_matrix(inter->fig->basis),
					inter->point);
		inter->point =
			scale_vector(inter->point,
				MULTIPLICATION, inter->fig->axis_dimensions);
		inter->point = matrix_mult_vect(inter->fig->basis, inter->point);
		inter->point = vect_sum(inter->point, inter->fig->origin);
		inter->distance = distance(inter->point, ray.origin);
		inter->normal = choose_normal(*inter->fig, inter->point);
	}
}

t_ray	find_ray_for_imaginary_sphere(t_ray ray, t_objects *ellipsoid)
{
	t_ray		new_ray;

	new_ray.origin = vect_diff(ray.origin, ellipsoid->origin);
	new_ray.origin =
		matrix_mult_vect(count_inverse_matrix(ellipsoid->basis),
			new_ray.origin);
	new_ray.origin = scale_vector(new_ray.origin, DIVISION,
			ellipsoid->axis_dimensions);
	new_ray.origin = matrix_mult_vect(ellipsoid->basis, new_ray.origin);
	new_ray.origin = vect_sum(new_ray.origin, ellipsoid->origin);
	new_ray.direction =
		matrix_mult_vect(count_inverse_matrix(ellipsoid->basis),
			ray.direction);
	new_ray.direction = scale_vector(new_ray.direction, DIVISION,
			ellipsoid->axis_dimensions);
	new_ray.direction = matrix_mult_vect(ellipsoid->basis, new_ray.direction);
	return (new_ray);
}
