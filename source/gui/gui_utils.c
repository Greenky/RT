/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 19:43:54 by ikachko           #+#    #+#             */
/*   Updated: 2018/08/02 11:42:15 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

char	*ftoa(float f, int tochnost)
{
	char	*first_part;
	char	*second_part;
	char	*buffer1;

	buffer1 = ft_itoa((int)f);
	if (f > -1 && f < 0 && (first_part = ft_strjoin("-", buffer1)))
		free(buffer1);
	else
		first_part = buffer1;
	if (f < 0)
		f *= -1;
	f = f - (int)f;
	while (tochnost > 0 && (f *= 10))
		tochnost--;
	second_part = ft_itoa((int)f);
	buffer1 = first_part;
	first_part = ft_strjoin(first_part, ".");
	free(buffer1);
	buffer1 = first_part;
	first_part = ft_strjoin(first_part, second_part);
	free(second_part);
	free(buffer1);
	return (first_part);
}

void	blit_surface_data(t_rt *rt_data, float fdata, SDL_Rect *pos)
{
	char		*str_data;
	SDL_Surface *text;

	str_data = ftoa(fdata, 1);
	text = TTF_RenderText_Shaded(rt_data->gui.open_sans, str_data,
	BLACK, WHITE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, pos);
	SDL_FreeSurface(text);
	free(str_data);
}

void	make_screenshot(t_rt *rt_data)
{
	SDL_Surface	*surface;
	SDL_Surface	*convert_surface;
	static int	img_num;
	char		*num;
	char		*scr_name;

	rt_data->take_screenshot = 1;
	draw_scene(rt_data);
	surface = SDL_GetWindowSurface(rt_data->window);
	convert_surface = SDL_ConvertSurfaceFormat(surface,
	SDL_PIXELFORMAT_RGB24, 0);
	SDL_FreeSurface(surface);
	num = ft_itoa(img_num);
	scr_name = ft_strjoin("ScreenShot", num);
	free(num);
	num = scr_name;
	scr_name = ft_strjoin(scr_name, ".jpg");
	free(num);
	SDL_SaveBMP(convert_surface, scr_name);
	free(scr_name);
	SDL_FreeSurface(convert_surface);
	rt_data->take_screenshot = 0;
	img_num++;
}

void	swap_cartoon(t_intersect closest_inter, t_rt *rt_data, int i)
{
	if (closest_inter.fig->type != PLANE
		&& closest_inter.fig->type != TRIANGLE
		&& closest_inter.fig == (rt_data->objects_arr + i))
		rt_data->objects_arr[i].is_cartoon =
				rt_data->objects_arr[i].is_cartoon ? 0 : 1;
	else
		rt_data->objects_arr[i].is_cartoon = 0;
}
