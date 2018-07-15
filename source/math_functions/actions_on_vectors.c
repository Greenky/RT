/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_on_vectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 20:42:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/09 20:42:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

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

t_vector	vect_mult_scalar(t_vector v1, float multiplier)
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

t_vector	vect_cross_product(t_vector a, t_vector b)
{
	t_vector c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
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

t_vector	scale_vector(t_vector v, int flag, t_vector scale_coef)
{
	if (flag == DIVISION)
	{
		v.x /= scale_coef.x;
		v.y /= scale_coef.y;
		v.z /= scale_coef.z;
	}
	else if (flag == MULTIPLICATION)
	{
		v.x *= scale_coef.x;
		v.y *= scale_coef.y;
		v.z *= scale_coef.z;
	}
	return (v);
}
