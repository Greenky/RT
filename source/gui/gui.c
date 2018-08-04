/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:15:46 by ikachko           #+#    #+#             */
/*   Updated: 2018/08/02 13:44:48 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void		draw_clicked_info(t_rt *rt_data)
{
	int	i;

	i = -1;
	while (++i < rt_data->cl_data.num_of_objects)
	{
		if (rt_data->objects_arr[i].is_cartoon)
		{
			draw_bar(rt_data);
			draw_object_info(rt_data, i);
		}
	}
}

void		draw_filter_bar(t_rt *rt_data)
{
	rt_data->gui.pos = (SDL_Rect){0, WIN_SIZE - 430, 0, 0};
	if (rt_data->filter == NONE)
		rt_data->filter = GREYSCALE;
	if (rt_data->filter == SEPIA)
		SDL_BlitSurface(rt_data->gui.sepia, NULL,
			rt_data->screen_surface, &rt_data->gui.pos);
	else if (rt_data->filter == GREYSCALE)
		SDL_BlitSurface(rt_data->gui.greyscale, NULL,
			rt_data->screen_surface, &rt_data->gui.pos);
	else if (rt_data->filter == NEGATIVE)
		SDL_BlitSurface(rt_data->gui.negative, NULL,
			rt_data->screen_surface, &rt_data->gui.pos);
	else if (rt_data->filter == PIXEL)
		SDL_BlitSurface(rt_data->gui.pixel, NULL,
			rt_data->screen_surface, &rt_data->gui.pos);
}

void		draw_foot_info(t_rt *rt_data)
{
	rt_data->gui.pos = (SDL_Rect){0, WIN_SIZE - 100, 0, 0};
	if (rt_data->aliasing == 2)
		SDL_BlitSurface(rt_data->gui.aliasing_on_foot, NULL,
						rt_data->screen_surface, &rt_data->gui.pos);
	else
		SDL_BlitSurface(rt_data->gui.aliasing_off_foot, NULL,
						rt_data->screen_surface, &rt_data->gui.pos);
	if (rt_data->gui.filter_gui)
		draw_filter_bar(rt_data);
}

void		draw_bar(t_rt *rt_data)
{
	SDL_BlitSurface(rt_data->gui.bar, NULL,
					rt_data->screen_surface, &rt_data->gui.bar_pos);
	SDL_BlitSurface(rt_data->gui.big_text_area, NULL,
					rt_data->screen_surface, &rt_data->gui.big_text_area_pos);
}

void		draw_gui(t_rt *rt_data)
{
	TTF_Init();
	if (!(rt_data->gui.c_font =
		TTF_OpenFont("fonts/OpenSans-Bold.ttf", 20))
			|| !(rt_data->gui.open_sans =
		TTF_OpenFont("fonts/OpenSans-Regular.ttf", 15)))
	{
		ft_putendl(SDL_GetError());
		exit(-1);
	}
	draw_clicked_info(rt_data);
	draw_foot_info(rt_data);
	TTF_CloseFont(rt_data->gui.c_font);
	TTF_CloseFont(rt_data->gui.open_sans);
	TTF_Quit();
}
