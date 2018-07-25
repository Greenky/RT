/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_color_disruptions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 22:29:14 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 22:29:15 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void		check_mate_disruption(SDL_Surface *surface)
{
	int	i;
	int	j;
	int	color;

	color = 0;
	j = -1;
	while (++j < surface->h)
	{
		i = -1;
		if (j % (surface->h / 64) == 0)
			color = (color == 0) ? 0xFFFFFF : 0;
		while (++i < surface->w)
		{
			if (i % (surface->w / 64) == 0)
				color = (color == 0) ? 0xFFFFFF : 0;
			set_pixel(surface, i, j, color);
		}
	}
}

void		plasma_disruption(SDL_Surface *surface)
{
	int			i;
	int			j;
	int			color;
	double		time;
	double		value;

	time = clock() / 50.0;
	j = -1;
	while (++j < surface->h)
	{
		i = -1;
		while (++i < surface->w)
		{
			value = sin(dist(i + time, j, surface->h / 2,
						surface->h / 2) / 8.0)
						+ sin(dist(i, j, surface->h / 4, surface->w / 4) / 8.0)
						+ sin(dist(i, j + time / 7, (surface->w / 4 * 3),
								surface->w / 4) / 7.0)
						+ sin(dist(i, j, (surface->w / 4 * 3), 100.0) / 8.0);
			color = (int)((4 + value)) * 32;
			set_pixel(surface, i, j,
					rgb_to_int((t_channel){color, color * 2, 255 - color}));
		}
	}
}
