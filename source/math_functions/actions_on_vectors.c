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
	cl_float3	vector;

	vector.x = v1.x - v2.x;
	vector.y = v1.y - v2.y;
	vector.z = v1.z - v2.z;
	return (vector);
}

cl_float3	vect_sum(cl_float3 v1, cl_float3 v2)
{
	cl_float3	vector;

	vector.x = v1.x + v2.x;
	vector.y = v1.y + v2.y;
	vector.z = v1.z + v2.z;
	return (vector);
}

cl_float3	vect_mult_scalar(cl_float3 v1, float multiplier)
{
	cl_float3	vector;

	vector.x = v1.x * multiplier;
	vector.y = v1.y * multiplier;
	vector.z = v1.z * multiplier;
	return (vector);
}

float		vect_scalar_mult(cl_float3 v1, cl_float3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
