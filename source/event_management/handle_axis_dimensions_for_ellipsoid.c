/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_axis_dimensions_for_ellipsoid.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 19:00:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/23 19:00:00 by dadavyde         ###   ########.fr       */
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

	ellipsoid->cap[0].dist = INFINITY;
	ellipsoid->cap[1].dist = INFINITY;
	biggest_axis = find_biggest_axis(ellipsoid);
	ellipsoid->radius = biggest_axis;
	ellipsoid->axis_dimensions =
			vect_mult_scalar(ellipsoid->axis_dimensions, 1 / biggest_axis);
}

void	check_axis_dimensions(float *length)
{
	if (*length < 0.05)
		*length = 0.05;
	if (*length > 10)
		*length = 10;
}

void	manage_ellipsoid_keys(int keycode, t_objects *ellipsoid)
{
	if (keycode == SDLK_KP_7)
		ellipsoid->axis_dimensions.x -= 0.1;
	else if (keycode == SDLK_KP_8)
		ellipsoid->axis_dimensions.x += 0.1;
	else if (keycode == SDLK_KP_4)
		ellipsoid->axis_dimensions.y -= 0.1;
	else if (keycode == SDLK_KP_5)
		ellipsoid->axis_dimensions.y += 0.1;
	else if (keycode == SDLK_KP_1)
		ellipsoid->axis_dimensions.z -= 0.1;
	else if (keycode == SDLK_KP_2)
		ellipsoid->axis_dimensions.z += 0.1;
}

void	manage_ellipsoid_axes(int keycode, t_rt *rt_data)
{
	t_objects	*ellipsoid;
	int			idx;

	idx = -1;
	ellipsoid = NULL;
	while (++idx < rt_data->cl_data.num_of_objects)
	{
		if (rt_data->objects_arr[idx].type == ELLIPSOID &&
			rt_data->objects_arr[idx].is_cartoon == 1)
		{
			ellipsoid = &(rt_data->objects_arr[idx]);
			break ;
		}
	}
	if (idx == rt_data->cl_data.num_of_objects)
		return ;
	ellipsoid->axis_dimensions =
		vect_mult_scalar(ellipsoid->axis_dimensions, ellipsoid->radius);
	manage_ellipsoid_keys(keycode, ellipsoid);
	check_axis_dimensions(&ellipsoid->axis_dimensions.x);
	check_axis_dimensions(&ellipsoid->axis_dimensions.y);
	check_axis_dimensions(&ellipsoid->axis_dimensions.z);
	handle_axis_dimensions(ellipsoid);
}
