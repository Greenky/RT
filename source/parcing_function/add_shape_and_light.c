/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 19:33:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/09 19:33:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void		add_shape(t_rt *rt_data, t_objects *shape)
{
	t_objects	*step;

    shape->basis = create_coord_system(shape->basis);
	shape->next = NULL;
	step = rt_data->objects;
	if (step)
	{
		while (step->next)
			step = step->next;
		step->next = shape;
	}
	else
		rt_data->objects = shape;
}

void		add_light(t_rt *rt_data, t_light *light)
{
	t_light *step;

	light->next = NULL;
	step = rt_data->lights;
	if (step)
	{
		while (step->next)
			step = step->next;
		step->next = light;
	}
	else
		rt_data->lights = light;
}
