/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebraic_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 20:44:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/09 20:44:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

float	find_square(float a)
{
	return (a * a);
}

float	distance(cl_float3 v1, cl_float3 v2)
{
	float	div_x;
	float	div_y;
	float	div_z;

	div_x = v2.x - v1.x;
	div_y = v2.y - v1.y;
	div_z = v2.z - v1.z;
	return (sqrtf(div_x * div_x + div_y * div_y + div_z * div_z));
}

float	length(cl_float3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}
