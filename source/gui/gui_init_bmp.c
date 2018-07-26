/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init_bmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 19:41:27 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 19:41:29 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void	init_bar_positions(t_rt *rt_data)
{
	rt_data->take_screenshot = 0;
	rt_data->gui.bar_pos = (SDL_Rect){0, 0, 0, 0};
	rt_data->gui.big_text_area_pos = (SDL_Rect){25, 25, 0, 0};
}

void	init_gui_bmps(t_rt *rt_data)
{
	if (!(rt_data->gui.bar = SDL_LoadBMP("gui_images/info_bar.bmp"))
		|| !(rt_data->gui.arrow_left_active =
							SDL_LoadBMP("gui_images/arrow_left_active.bmp"))
		|| !(rt_data->gui.arrow_right_active =
							SDL_LoadBMP("gui_images/arrow_right_active.bmp")))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.arrow_left_unactive =
				SDL_LoadBMP("gui_images/arrow_left_unactive.bmp")))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.arrow_right_unactive =
				SDL_LoadBMP("gui_images/arrow_right_unactive.bmp")))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.little_text_area =
				SDL_LoadBMP("gui_images/little_text_area.bmp")))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.big_text_area =
				SDL_LoadBMP("gui_images/big_text_area.bmp")))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.checked =
				SDL_LoadBMP("gui_images/checked.bmp")))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.unchecked =
				SDL_LoadBMP("gui_images/unchecked.bmp")))
		error_exit(LOAD_BMP_ERROR, rt_data);
}

void	init_foot_gui_bmps(t_rt *rt_data)
{
	if (!(rt_data->gui.aliasing_on_foot = SDL_LoadBMP(GUI_ALIAS_ON_BMP)))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.aliasing_off_foot = SDL_LoadBMP(GUI_ALIAS_OFF_BMP)))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.sepia = SDL_LoadBMP(GUI_SEPIA_BMP)))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.greyscale = SDL_LoadBMP(GUI_GREYSCALE_BMP)))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.negative = SDL_LoadBMP(GUI_NEGATIVE_BMP)))
		error_exit(LOAD_BMP_ERROR, rt_data);
	if (!(rt_data->gui.pixel = SDL_LoadBMP(GUI_PIXEL_BMP)))
		error_exit(LOAD_BMP_ERROR, rt_data);
}
