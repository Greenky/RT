/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_draw_objects_info_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 18:56:20 by ikachko           #+#    #+#             */
/*   Updated: 2018/08/01 21:39:52 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

static void	draw_text(SDL_Surface *text, t_rt *rt_data, SDL_Rect pos)
{
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
}

static void	draw_ellipsoid_info_2(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;
	SDL_Surface	*text;

	pos = (SDL_Rect){88, 175, 0, 0};
	sphere_control_bars_show(rt_data, pos, POS_X, object);
	pos = (SDL_Rect){88, 183, 0, 0};
	blit_surface_data(rt_data, object->origin.x, &pos);
	pos = (SDL_Rect){85, 210, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Y: ", BLACK, D_BLUE);
	draw_text(text, rt_data, pos);
	pos = (SDL_Rect){88, 230, 0, 0};
	sphere_control_bars_show(rt_data, pos, POS_Y, object);
	pos = (SDL_Rect){88, 238, 0, 0};
	blit_surface_data(rt_data, object->origin.y, &pos);
	pos = (SDL_Rect){85, 265, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Z: ", BLACK, D_BLUE);
	draw_text(text, rt_data, pos);
	pos = (SDL_Rect){88, 285, 0, 0};
	sphere_control_bars_show(rt_data, pos, POS_Z, object);
	pos = (SDL_Rect){88, 293, 0, 0};
	blit_surface_data(rt_data, object->origin.z, &pos);
}

void		draw_ellipsoid_info(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;
	SDL_Surface	*text;

	text = TTF_RenderText_Shaded(rt_data->gui.c_font, " Ellipsoid",
	BLACK, WHITE);
	draw_text(text, rt_data, (SDL_Rect){36, 35, 0, 0});
	pos = (SDL_Rect){26, 97, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.open_sans,
	"Radius1 -/+  -> 1/2", BLACK, D_BLUE);
	draw_text(text, rt_data, pos);
	pos = (SDL_Rect){26, 117, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.open_sans,
	"Radius2 -/+  -> 4/5", BLACK, D_BLUE);
	draw_text(text, rt_data, pos);
	pos = (SDL_Rect){26, 137, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.open_sans,
	"Radius3 -/+  -> 7/8 ", BLACK, D_BLUE);
	draw_text(text, rt_data, pos);
	pos = (SDL_Rect){85, 155, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "X: ",
	BLACK, D_BLUE);
	draw_text(text, rt_data, pos);
	draw_ellipsoid_info_2(rt_data, object);
}

static void	draw_sphere_info_2(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;
	SDL_Surface	*text;

	pos = (SDL_Rect){85, 210, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Y: ", BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 230, 0, 0};
	sphere_control_bars_show(rt_data, pos, POS_Y, object);
	pos = (SDL_Rect){88, 238, 0, 0};
	blit_surface_data(rt_data, object->origin.y, &pos);
	pos = (SDL_Rect){85, 265, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Z: ", BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 285, 0, 0};
	sphere_control_bars_show(rt_data, pos, POS_Z, object);
	pos = (SDL_Rect){88, 293, 0, 0};
	blit_surface_data(rt_data, object->origin.z, &pos);
}

void		draw_sphere_info(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;
	SDL_Surface	*text;

	pos = (SDL_Rect){50, 35, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Sphere", BLACK, WHITE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){56, 100, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Radius: ",
	BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 120, 0, 0};
	sphere_control_bars_show(rt_data, pos, RADIUS, object);
	pos = (SDL_Rect){88, 128, 0, 0};
	blit_surface_data(rt_data, object->radius, &pos);
	pos = (SDL_Rect){85, 155, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "X: ", BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 175, 0, 0};
	sphere_control_bars_show(rt_data, pos, POS_X, object);
	pos = (SDL_Rect){88, 183, 0, 0};
	blit_surface_data(rt_data, object->origin.x, &pos);
	draw_sphere_info_2(rt_data, object);
}
