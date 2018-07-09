/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebraic_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 20:10:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/05/30 20:12:43 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

float	find_square(float a)
{
	return (a * a);
}

float	distance(t_vector v1, t_vector v2)
{
	float	div_x;
	float	div_y;
	float	div_z;

	div_x = v2.x - v1.x;
	div_y = v2.y - v1.y;
	div_z = v2.z - v1.z;
	return (sqrtf(div_x * div_x + div_y * div_y + div_z * div_z));
}

float	length(t_vector v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}
