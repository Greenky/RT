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

float	distance(t_vector v1, t_vector v2)
{
	float	div_x;
	float	div_y;
	float	div_z;

	div_x = v2.x - v1.x;
	div_y = v2.y - v1.y;
	div_z = v2.z - v1.z;
	return (sqrtf(find_square(div_x) + find_square(div_y) + find_square(div_z)));
}

float	length(t_vector v)
{
	return (sqrtf(find_square(v.x) + find_square(v.y)+ find_square(v.z)));
}
