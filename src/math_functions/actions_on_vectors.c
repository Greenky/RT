/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_on_vectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 19:37:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 12:34:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

t_vector	vect_diff(t_vector v1, t_vector v2)
{
	t_vector	result_vector;

	result_vector.x = v1.x - v2.x;
	result_vector.y = v1.y - v2.y;
	result_vector.z = v1.z - v2.z;
	return (result_vector);
}

t_vector	vect_sum(t_vector v1, t_vector v2)
{
	t_vector	result_vector;

	result_vector.x = v1.x + v2.x;
	result_vector.y = v1.y + v2.y;
	result_vector.z = v1.z + v2.z;
	return (result_vector);
}

t_vector	vect_mult(t_vector v1, float multiplier)
{
	t_vector	result_vector;

	result_vector.x = v1.x * multiplier;
	result_vector.y = v1.y * multiplier;
	result_vector.z = v1.z * multiplier;
	return (result_vector);
}

float		vect_scalar_mult(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	normalize_vector(t_vector a)
{
	float		coef;
	t_vector	normal;
	float		len;

	len = length(a);
	if (len == 0)
		return ((t_vector){0, 0, 0});
	coef = 1.0f / len;
	normal.x = a.x * coef;
	normal.y = a.y * coef;
	normal.z = a.z * coef;
	return (normal);
}
