/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 14:23:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 13:34:58 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void		event_management(t_rt *rt_data, SDL_Event *event)
{
	int			running;
	cl_float3	res;

	running = 1;
	SDL_UpdateWindowSurface(rt_data->window);
	res.x = 0;
	res.y = 0;
	res.z = 0;
	rt_data->cl_data.camera.angle_rot = res;
	while (running)
	{
		while (SDL_PollEvent(event))
		{
			if (!exit_x(rt_data, event))
				running = 0;
			if (event->type == SDL_KEYDOWN)
				key_down(rt_data, event);
			if (event->type == SDL_MOUSEBUTTONDOWN)
				mouse_click_event(rt_data, event);
		}
	}
}

int			exit_x(t_rt *rt_data, SDL_Event *event)
{
	if (event->type == SDL_QUIT
		|| (event->type == SDL_KEYDOWN &&
		event->key.keysym.scancode == SDL_SCANCODE_ESCAPE))
	{

		SDL_FreeSurface(rt_data->screen_surface);
		SDL_FreeSurface(rt_data->gui.bar);
		SDL_FreeSurface(rt_data->gui.arrow_left_active);
		SDL_FreeSurface(rt_data->gui.arrow_right_active);
		SDL_FreeSurface(rt_data->gui.arrow_left_unactive);
		SDL_FreeSurface(rt_data->gui.arrow_right_unactive);
		SDL_FreeSurface(rt_data->gui.little_text_area);
		SDL_FreeSurface(rt_data->gui.big_text_area);
		SDL_FreeSurface(rt_data->gui.checked);
		SDL_FreeSurface(rt_data->gui.unchecked);
		SDL_FreeSurface(rt_data->gui.aliasing_on_foot);
		SDL_FreeSurface(rt_data->gui.sepia);
		SDL_FreeSurface(rt_data->gui.greyscale);
		SDL_FreeSurface(rt_data->gui.pixel);
		SDL_FreeSurface(rt_data->gui.negative);
		SDL_DestroyWindow(rt_data->window);
		SDL_Quit();
		return (0);
	}
	else
		return (1);
}

int			key_down(t_rt *rt_data, SDL_Event *event)
{
	if (check_camera_key(event->key.keysym.sym, SHIFT))
		manage_camera_origin(event->key.keysym.sym, rt_data);
	else if (check_camera_key(event->key.keysym.sym, ROTATE))
		rotating_camera(event->key.keysym.sym, rt_data);
	else if (event->key.keysym.sym == SDLK_SPACE)
		reset_camera_settings(rt_data);
	else if (event->key.keysym.sym >= SDLK_KP_1
			&& event->key.keysym.sym <= SDLK_KP_0)
		manage_ellipsoid_axes(event->key.keysym.sym, rt_data);
	else
		return (0);

	draw_scene(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	return (0);
}

int			check_camera_key(int keycode, int type_of_motion)
{
	if (type_of_motion == ROTATE)
	{
		if (keycode == SDLK_UP || keycode == SDLK_DOWN
			|| keycode == SDLK_RIGHT || keycode == SDLK_LEFT
			|| keycode == SDLK_PAGEUP || keycode == SDLK_PAGEDOWN)
			return (TRUE);
		else
			return (FALSE);
	}
	else if (type_of_motion == SHIFT)
	{
		if (keycode == SDLK_w || keycode == SDLK_s
			|| keycode == SDLK_d || keycode == SDLK_a)
			return (TRUE);
		else
			return (FALSE);
	}
	else
		return (FALSE);
}
