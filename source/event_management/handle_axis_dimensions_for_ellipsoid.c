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

void	manage_ellipsoid_axes(int keycode, t_rt *rt_data)
{
	t_objects	*fig;

	fig = &(rt_data->objects_arr[0]);
	/*while (fig && fig->type != SPHERE)//check selection ellipsoid
		fig = fig->next;//change when user interface will be
	if (fig == NULL)
		return;*/
	fig->axis_dimensions = vect_mult_scalar(fig->axis_dimensions, fig->radius);
	if (keycode == SDLK_KP_7)
		fig->axis_dimensions.x -= 0.1;
	else if (keycode == SDLK_KP_8)
		fig->axis_dimensions.x += 0.1;
	else if (keycode == SDLK_KP_4)
		fig->axis_dimensions.y -= 0.1;
	else if (keycode == SDLK_KP_5)
		fig->axis_dimensions.y += 0.1;
	else if (keycode == SDLK_KP_1)
		fig->axis_dimensions.z -= 0.1;
	else if (keycode == SDLK_KP_2)
		fig->axis_dimensions.z += 0.1;
	check_axis_dimensions(&fig->axis_dimensions.x);
	check_axis_dimensions(&fig->axis_dimensions.y);
	check_axis_dimensions(&fig->axis_dimensions.z);
	handle_axis_dimensions(fig);
	printf("axis_dimensions.x = %f, axis_dimensions.y = %f, axis_dimensions.z = %f\n",
		fig->axis_dimensions.x, fig->axis_dimensions.y, fig->axis_dimensions.z);//TODO delete
}
