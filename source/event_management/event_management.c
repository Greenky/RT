/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 14:23:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/01 20:27:12 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void		client_event_management(t_rt *rt_data, SDL_Event *event)
{
	while (rt_data->is_client)
	{
		event = (SDL_Event *)receive_data(rt_data->server_fd, event,
		sizeof(SDL_Event));
		if (event->type == SDL_QUIT
			|| (event->type == SDL_KEYDOWN &&
				event->key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			exit(0);
		if (event->type == SDL_KEYDOWN)
			key_down(rt_data, event);
		if (event->type == SDL_MOUSEBUTTONDOWN)
			mouse_click_event(rt_data, event);
	}
}

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
		while (!rt_data->is_client && SDL_PollEvent(event))
		{
			if (!exit_x(rt_data, event))
				running = 0;
			if (event->type == SDL_KEYDOWN)
				key_down(rt_data, event);
			if (event->type == SDL_MOUSEBUTTONDOWN)
				mouse_click_event(rt_data, event);
		}
		client_event_management(rt_data, event);
	}
}

int			exit_x(t_rt *rt_data, SDL_Event *event)
{
	if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN &&
		event->key.keysym.scancode == SDL_SCANCODE_ESCAPE))
	{
		send_data(rt_data->server_fd, event, sizeof(SDL_Event));
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
	if (check_sdl_key(event->key.keysym.sym, SHIFT))
		manage_camera_origin(event->key.keysym.sym, rt_data);
	else if (check_sdl_key(event->key.keysym.sym, ROTATE))
		rotating_object(event->key.keysym.sym, rt_data);
	else if (event->key.keysym.sym == SDLK_SPACE)
		reset_camera_settings(rt_data);
	else if (event->key.keysym.sym >= SDLK_KP_1
			&& event->key.keysym.sym <= SDLK_KP_0)
		manage_ellipsoid_axes(event->key.keysym.sym, rt_data);
	else
		return (0);
	if (rt_data->server_mode)
		send_data(rt_data->server_fd, event, sizeof(SDL_Event));
	draw_scene(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	return (0);
}

int			check_sdl_key(int keycode, int type_of_motion)
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
