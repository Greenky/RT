/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_control_bars_show.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 18:36:47 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 18:36:48 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void		arrows_active_unactive(t_rt *rt_data,
								SDL_Rect pos, float *min_max, float value)
{
	SDL_Rect	left;
	SDL_Rect	right;
	SDL_Rect	text;

	left.x = pos.x - 80;
	left.y = pos.y;
	right.x = pos.x + 50;
	right.y = pos.y;
	text.x = left.x + 35;
	text.y = pos.y + 6;
	SDL_BlitSurface(rt_data->gui.little_text_area, NULL,
					rt_data->screen_surface, &text);
	if (value >= min_max[0])
		SDL_BlitSurface(rt_data->gui.arrow_left_active, NULL,
						rt_data->screen_surface, &left);
	else
		SDL_BlitSurface(rt_data->gui.arrow_left_unactive, NULL,
						rt_data->screen_surface, &left);
	if (value <= min_max[1])
		SDL_BlitSurface(rt_data->gui.arrow_right_active, NULL,
						rt_data->screen_surface, &right);
	else
		SDL_BlitSurface(rt_data->gui.arrow_right_unactive, NULL,
						rt_data->screen_surface, &right);
}

void		sphere_control_bars_show(t_rt *rt_data,
									SDL_Rect pos, int flag, t_objects *sphere)
{
	float		min_max[2];

	min_max[0] = -100;
	min_max[1] = 100;
	if (flag == RADIUS)
	{
		min_max[0] = 0.5;
		min_max[1] = 50.0;
		arrows_active_unactive(rt_data, pos, min_max, sphere->radius);
	}
	else if (flag == POS_X)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.x);
	else if (flag == POS_Y)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.y);
	else if (flag == POS_Z)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.z);
}

void		cylinder_control_bars_show(t_rt *rt_data,
									SDL_Rect pos, int flag, t_objects *sphere)
{
	float		min_max[2];

	min_max[0] = -100;
	min_max[1] = 100;
	if (flag == RADIUS)
	{
		min_max[0] = 1.0;
		min_max[1] = 50.0;
		arrows_active_unactive(rt_data, pos, min_max, sphere->radius);
	}
	else if (flag == POS_X)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.x);
	else if (flag == POS_Y)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.y);
	else if (flag == POS_Z)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.z);
}

void		cone_control_bars_show(t_rt *rt_data,
								SDL_Rect pos, int flag, t_objects *sphere)
{
	float		min_max[2];

	min_max[0] = -100;
	min_max[1] = 100;
	if (flag == ANGLE_KOEF)
	{
		min_max[0] = 0.2;
		min_max[1] = 3.0;
		arrows_active_unactive(rt_data, pos, min_max, sphere->angle_coef);
	}
	else if (flag == POS_X)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.x);
	else if (flag == POS_Y)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.y);
	else if (flag == POS_Z)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.z);
}
