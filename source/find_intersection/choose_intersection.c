/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 17:44:22 by vmazurok          #+#    #+#             */
/*   Updated: 2018/07/26 17:44:50 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void		choose_intersection(t_ray primary_ray, t_intersect *tmp_inter)
{
	if (tmp_inter->fig->type == SPHERE)
		sphere_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == CYLINDER)
		cyl_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == CONE)
		cone_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == PLANE)
		plane_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == ELLIPSOID)
		ellipsoid_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == TRIANGLE)
		triangle_find_closest_intersect(primary_ray, tmp_inter);
}
