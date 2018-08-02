/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_normal_to_figure.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:44:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/13 20:09:28 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

cl_float3	choose_normal(t_objects figure, cl_float3 inter)
{
	cl_float3 nor;

	if (figure.type == SPHERE)
		return (find_normal_to_sphere(figure, inter));
	else if (figure.type == CYLINDER)
		return (find_normal_to_cylinder(figure, inter));
	else if (figure.type == CONE)
	{
		nor = find_normal_to_cone(figure, inter);
		if (nor.x != nor.x)
			nor = VEC(1, 0, 0);
		return (nor);
	}
	else if (figure.type == PLANE)
		return (find_normal_to_plane(figure, inter));
	else if (figure.type == ELLIPSOID)
		return (find_normal_to_ellipsoid(figure, inter));
	else if (figure.type == TRIANGLE)
		return (find_normal_to_plane(figure, inter));
	else
		return (VEC(1, 1, 1));
}
