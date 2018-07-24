/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 19:43:54 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 19:43:56 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

char*	ftoa(float f, int tochnost)
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

void		blit_surface_data(t_rt *rt_data, float fdata, SDL_Rect *pos)
{
	char		*str_data;

	str_data = ftoa(fdata, 1);
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.open_sans, str_data, BLACK, WHITE), NULL, rt_data->screen_surface, pos);
	free(str_data);
}

void		sdl_error(char *str)
{
	ft_putstr(str);
	ft_putendl(SDL_GetError());
	exit(1);
}