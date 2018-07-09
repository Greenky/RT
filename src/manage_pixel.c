/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:41:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/03 16:26:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void		set_pixel(SDL_Surface *surface, int x, int y, uint32_t color)
{
	((uint32_t*)surface->pixels)[y * surface->w + x] = color;
}
