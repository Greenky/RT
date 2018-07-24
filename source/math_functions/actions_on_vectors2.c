/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_on_vectors2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:04:28 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 14:04:30 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

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

cl_float3	scale_vector(cl_float3 v, int flag, cl_float3 mult_coef)
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
