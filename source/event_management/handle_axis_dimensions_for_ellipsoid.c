/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_axis_dimensions_for_ellipsoid.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 21:47:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/12 21:47:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

float	find_biggest_axis(t_objects *ellipsoid)
{
	float		biggest_axis;

	biggest_axis = ellipsoid->axis_dimensions.x;
	if (ellipsoid->axis_dimensions.y > biggest_axis)
		biggest_axis = ellipsoid->axis_dimensions.y;
	if (ellipsoid->axis_dimensions.z > biggest_axis)
		biggest_axis = ellipsoid->axis_dimensions.z;
	return (biggest_axis);
}

void	handle_axis_dimensions(t_objects *ellipsoid)
{
	float		biggest_axis;

	biggest_axis = find_biggest_axis(ellipsoid);
	ellipsoid->radius = biggest_axis;
	ellipsoid->axis_dimensions = vect_mult_scalar(ellipsoid->axis_dimensions, 1 / biggest_axis);
	//printf("axis_dimensions.x = %f, axis_dimensions.y = %f, axis_dimensions.z = %f\n", ellipsoid->axis_dimensions.x, ellipsoid->axis_dimensions.y, ellipsoid->axis_dimensions.z);//TODO delete
}

void	check_axis_dimensions(float *length)
{
	if (*length < 0.05)
		*length = 0.05;
	if (*length > 10)
		*length = 10;
}
