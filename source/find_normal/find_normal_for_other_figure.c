/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_normal_for_other_figure.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:44:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/13 20:09:28 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

t_vector	find_normal_to_ellipsoid(t_objects *ellipsoid, t_vector inter)
{
	t_vector	normal_to_ellipsoid;

	normal_to_ellipsoid.x = inter.x / 2 / find_square(ellipsoid->axis_dimensions.x * ellipsoid->radius);
	normal_to_ellipsoid.y = inter.y / 2 / find_square(ellipsoid->axis_dimensions.y * ellipsoid->radius);
	normal_to_ellipsoid.z = inter.z / 2 / find_square(ellipsoid->axis_dimensions.z * ellipsoid->radius);
	normal_to_ellipsoid = vect_mult_scalar(normalize_vector(normal_to_ellipsoid), -1);
	return(normal_to_ellipsoid);
}
