/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_object_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:29:18 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 17:29:19 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void	change_sphere(t_objects *object, int arrow)
{
	if (arrow == LEFT1 && object->radius >= 0.5)
		object->radius -= 0.1;
	else if (arrow == RIGHT1 && object->radius <= 50.0)
		object->radius += 0.1;
	else if (arrow == LEFT2)
		object->origin.x -= 0.1;
	else if (arrow == RIGHT2)
		object->origin.x += 0.1;
	else if (arrow == LEFT3)
		object->origin.y -= 0.1;
	else if (arrow == RIGHT3)
		object->origin.y += 0.1;
	else if (arrow == LEFT4)
		object->origin.z -= 0.1;
	else if (arrow == RIGHT4)
		object->origin.z += 0.1;
}

void	change_cylinder(t_objects *object, int arrow)
{
	if (arrow == LEFT1 && object->radius >= 1.0)
		object->radius -= 0.1;
	else if (arrow == RIGHT1 && object->radius <= 50.0)
		object->radius += 0.1;
	else if (arrow == LEFT2)
		object->origin.x -= 0.1;
	else if (arrow == RIGHT2)
		object->origin.x += 0.1;
	else if (arrow == LEFT3)
		object->origin.y -= 0.1;
	else if (arrow == RIGHT3)
		object->origin.y += 0.1;
	else if (arrow == LEFT4)
		object->origin.z -= 0.1;
	else if (arrow == RIGHT4)
		object->origin.z += 0.1;
}

void	change_cone(t_objects *object, int arrow)
{
	if (arrow == LEFT1 && object->angle_coef >= 0.2)
		object->angle_coef -= 0.1;
	else if (arrow == RIGHT1 && object->angle_coef <= 3.0)
		object->angle_coef += 0.1;
	else if (arrow == LEFT2)
		object->origin.x -= 0.1;
	else if (arrow == RIGHT2)
		object->origin.x += 0.1;
	else if (arrow == LEFT3)
		object->origin.y -= 0.1;
	else if (arrow == RIGHT3)
		object->origin.y += 0.1;
	else if (arrow == LEFT4)
		object->origin.z -= 0.1;
	else if (arrow == RIGHT4)
		object->origin.z += 0.1;
}

void	change_object(t_objects *object, int arrow)
{
	if (object->type == SPHERE || object->type == ELLIPSOID)
		change_sphere(object, arrow);
	else if (object->type == CYLINDER)
		change_cylinder(object, arrow);
	else if (object->type == CONE)
		change_cone(object, arrow);
}
