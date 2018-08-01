/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_draw_objects_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 18:46:56 by ikachko           #+#    #+#             */
/*   Updated: 2018/08/01 21:16:55 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void		draw_cylinder_info_2(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;
	SDL_Surface *text;

	pos = (SDL_Rect){88, 183, 0, 0};
	blit_surface_data(rt_data, object->origin.x, &pos);
	pos = (SDL_Rect){85, 210, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Y: ", BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 230, 0, 0};
	cylinder_control_bars_show(rt_data, pos, POS_Y, object);
	pos = (SDL_Rect){88, 238, 0, 0};
	blit_surface_data(rt_data, object->origin.y, &pos);
	pos = (SDL_Rect){85, 265, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Z: ", BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 285, 0, 0};
	cylinder_control_bars_show(rt_data, pos, POS_Z, object);
	pos = (SDL_Rect){88, 293, 0, 0};
	blit_surface_data(rt_data, object->origin.z, &pos);
}

void		draw_cylinder_info(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;
	SDL_Surface *text;

	pos = (SDL_Rect){45, 35, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Cylinder", BLACK, WHITE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){56, 100, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Radius: ",
	BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 120, 0, 0};
	cylinder_control_bars_show(rt_data, pos, RADIUS, object);
	pos = (SDL_Rect){88, 128, 0, 0};
	blit_surface_data(rt_data, object->radius, &pos);
	pos = (SDL_Rect){85, 155, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "X: ", BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 175, 0, 0};
	cylinder_control_bars_show(rt_data, pos, POS_X, object);
	draw_cylinder_info_2(rt_data, object);
}

static void	draw_cone_info_2(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;
	SDL_Surface *text;

	pos = (SDL_Rect){85, 210, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Y: ", BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 230, 0, 0};
	cone_control_bars_show(rt_data, pos, POS_Y, object);
	pos = (SDL_Rect){88, 238, 0, 0};
	blit_surface_data(rt_data, object->origin.y, &pos);
	pos = (SDL_Rect){85, 265, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Z: ", BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 285, 0, 0};
	cone_control_bars_show(rt_data, pos, POS_Z, object);
	pos = (SDL_Rect){88, 293, 0, 0};
	blit_surface_data(rt_data, object->origin.z, &pos);
}

void		draw_cone_info(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;
	SDL_Surface *text;

	pos = (SDL_Rect){45, 35, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Cone", BLACK, WHITE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){56, 100, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "Angle: ", BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 120, 0, 0};
	cone_control_bars_show(rt_data, pos, ANGLE_KOEF, object);
	pos = (SDL_Rect){88, 128, 0, 0};
	blit_surface_data(rt_data, object->angle_coef, &pos);
	pos = (SDL_Rect){85, 155, 0, 0};
	text = TTF_RenderText_Shaded(rt_data->gui.c_font, "X: ", BLACK, D_BLUE);
	SDL_BlitSurface(text, NULL, rt_data->screen_surface, &pos);
	SDL_FreeSurface(text);
	pos = (SDL_Rect){88, 175, 0, 0};
	cone_control_bars_show(rt_data, pos, POS_X, object);
	pos = (SDL_Rect){88, 183, 0, 0};
	blit_surface_data(rt_data, object->origin.x, &pos);
	draw_cone_info_2(rt_data, object);
}

void		draw_object_info(t_rt *rt_data, int i)
{
	if (rt_data->objects_arr[i].type == SPHERE)
		draw_sphere_info(rt_data, &rt_data->objects_arr[i]);
	else if (rt_data->objects_arr[i].type == CYLINDER)
		draw_cylinder_info(rt_data, &rt_data->objects_arr[i]);
	else if (rt_data->objects_arr[i].type == CONE)
		draw_cone_info(rt_data, &rt_data->objects_arr[i]);
	else if (rt_data->objects_arr[i].type == ELLIPSOID)
		draw_ellipsoid_info(rt_data, &rt_data->objects_arr[i]);
}
