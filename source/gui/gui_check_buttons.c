/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_check_buttons.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:33:54 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 17:33:58 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

int		check_arrow_type(SDL_Event *event)
{
	if (event->button.x >= 8 && event->button.x <= 58
		&& event->button.y >= 125 && event->button.y <= 165)
		return (LEFT1);
	if (event->button.x >= 138 && event->button.x <= 188
		&& event->button.y >= 120 && event->button.y <= 160)
		return (RIGHT1);
	if (event->button.x >= 8 && event->button.x <= 58
		&& event->button.y >= 175 && event->button.y <= 215)
		return (LEFT2);
	if (event->button.x >= 138 && event->button.x <= 188
		&& event->button.y >= 175 && event->button.y <= 215)
		return (RIGHT2);
	if (event->button.x >= 8 && event->button.x <= 58
		&& event->button.y >= 230 && event->button.y <= 270)
		return (LEFT3);
	if (event->button.x >= 138 && event->button.x <= 188
		&& event->button.y >= 230 && event->button.y <= 270)
		return (RIGHT3);
	if (event->button.x >= 8 && event->button.x <= 58
		&& event->button.y >= 285 && event->button.y <= 325)
		return (LEFT4);
	if (event->button.x >= 138 && event->button.x <= 188
		&& event->button.y >= 285 && event->button.y <= 325)
		return (RIGHT4);
	return (NONE);
}

int		check_foot_press_type(SDL_Event *event)
{
	if (event->button.x >= 0 && event->button.x <= 195
		&& event->button.y >= WIN_SIZE - 150 && event->button.y <= WIN_SIZE)
		return (FILTERS);
	else if (event->button.x >= 600 && event->button.x <= 680
			&& event->button.y >= WIN_SIZE - 83
			&& event->button.y <= WIN_SIZE - 20)
		return (ALIASING);
	else if (event->button.x >= 195 && event->button.x <= 550
			&& event->button.y >= WIN_SIZE - 150 && event->button.y <= WIN_SIZE)
		return (SAVE);
	return (NONE);
}

int		check_if_in_gui(t_rt *rt_data, SDL_Event *event)
{
	if (event->button.x >= 0 && event->button.x <= 200
		&& event->button.y >= 0 && event->button.y <= 400)
		return (FIGURE_GUI);
	else if (rt_data->gui.filter_gui
			&& event->button.x >= 0 && event->button.x <= 300
			&& event->button.y >= WIN_SIZE - 430
			&& event->button.y <= WIN_SIZE - 100)
		return (FILTER_GUI);
	else if (event->button.x >= 0 && event->button.x <= 700
			&& event->button.y >= WIN_SIZE - 100
			&& event->button.y <= WIN_SIZE)
		return (FOOT_GUI);
	else
		return (NO_GUI);
}
