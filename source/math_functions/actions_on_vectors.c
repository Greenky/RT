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

cl_float3	vect_diff(cl_float3 v1, cl_float3 v2)
{
	cl_float3	resulcl_float3;

	resulcl_float3.x = v1.x - v2.x;
	resulcl_float3.y = v1.y - v2.y;
	resulcl_float3.z = v1.z - v2.z;
	return (resulcl_float3);
}

cl_float3	vect_sum(cl_float3 v1, cl_float3 v2)
{
	cl_float3	resulcl_float3;

	resulcl_float3.x = v1.x + v2.x;
	resulcl_float3.y = v1.y + v2.y;
	resulcl_float3.z = v1.z + v2.z;
	return (resulcl_float3);
}

cl_float3	vect_mult_scalar(cl_float3 v1, float multiplier)
{
	cl_float3	resulcl_float3;

	resulcl_float3.x = v1.x * multiplier;
	resulcl_float3.y = v1.y * multiplier;
	resulcl_float3.z = v1.z * multiplier;
	return (resulcl_float3);
}

float		vect_scalar_mult(cl_float3 v1, cl_float3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

cl_float3	vect_cross_product(cl_float3 a, cl_float3 b)
{
	cl_float3 c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

cl_float3	normalize_vector(cl_float3 a)
{
	float		coef;
	cl_float3	normal;
	float		len;

	len = length(a);
	if (len == 0)
	{
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		return (normal);
	}
	coef = 1.0f / len;
	normal.x = a.x * coef;
	normal.y = a.y * coef;
	normal.z = a.z * coef;
	return (normal);
}

cl_float3	change_vector(cl_float3 v,  int flag, cl_float3 mult_coef)
{
	if (flag == DIVISION)
	{
		v.x /= mult_coef.x;
		v.y /= mult_coef.y;
		v.z /= mult_coef.z;
	}
	else if (flag == MULTIPLICATION)
	{
		v.x *= mult_coef.x;
		v.y *= mult_coef.y;
		v.z *= mult_coef.z;
	}
	return (v);
}
