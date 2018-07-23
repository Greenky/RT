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

int		check_arrow_type(SDL_Event *event)
{
	if (event->button.x >= 8 && event->button.x <= 58
		&& event->button.y >= 125 && event->button.y <= 165)
		return (LEFT1);
	if (event->button.x >= 138 && event->button.x <= 188
		&& event->button.y >= 120 && event->button.y <= 160)
		return (RIGHT1);
	if (event->button.x >= 8 && event->button.x <= 58
		&& event->button.y >= 175 && event->button.y <= 215)
		return (LEFT2);
	if (event->button.x >= 138 && event->button.x <= 188
		&& event->button.y >= 175 && event->button.y <= 215)
		return (RIGHT2);
	if (event->button.x >= 8 && event->button.x <= 58
		&& event->button.y >= 230 && event->button.y <= 270)
		return (LEFT3);
	if (event->button.x >= 138 && event->button.x <= 188
		&& event->button.y >= 230 && event->button.y <= 270)
		return (RIGHT3);
	if (event->button.x >= 8 && event->button.x <= 58
		&& event->button.y >= 285 && event->button.y <= 325)
		return (LEFT4);
	if (event->button.x >= 138 && event->button.x <= 188
		&& event->button.y >= 285 && event->button.y <= 325)
		return (RIGHT4);
	return (NONE);
}

void	gui_interaction_event(t_rt *rt_data, SDL_Event *event)
{
	int	i;

	i = -1;
	while (++i < rt_data->cl_data.num_of_objects)
	{
		if (rt_data->objects_arr[i].is_cartoon)
			change_object(&rt_data->objects_arr[i], check_arrow_type(event));
	}
}

int		check_foot_press_type(SDL_Event *event)
{
	if (event->button.x >= 0 && event->button.x <= 195
		&& event->button.y >= SCR_SIZE - 150 && event->button.y <= SCR_SIZE)
		return (FILTERS);
	else if (event->button.x >= 600 && event->button.x <= 680
			&& event->button.y >= SCR_SIZE - 83 && event->button.y <= SCR_SIZE - 20)
		return (ALIASING);
	else if (event->button.x >= 195 && event->button.x <= 550
			&& event->button.y >= SCR_SIZE - 150 && event->button.y <= SCR_SIZE)
		return (SAVE);
	return (NONE);
}

void	foot_panel_interaction_event(t_rt *rt_data, SDL_Event *event)
{
	int			flag;
	SDL_Surface	*surface;
	static int	img_num;
	char		*num;
	char		*scr_name;

	flag = check_foot_press_type(event);
	if (flag == FILTERS)
	{
		rt_data->gui.filter_gui = !rt_data->gui.filter_gui;
		rt_data->filter = NONE;
	}
	else if (flag == ALIASING)
		rt_data->aliasing = !rt_data->aliasing;
	else
	{
		rt_data->take_screenshot = 1;
		draw_scene(rt_data);
		surface = SDL_GetWindowSurface(rt_data->window);
		surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB24, 0);
		num = ft_itoa(img_num);
		scr_name = ft_strjoin("ScreenShot", num);
		free(num);
		num = scr_name;
		scr_name = ft_strjoin(scr_name, ".jpg");
		free(num);
		SDL_SaveBMP(surface, scr_name);
		rt_data->take_screenshot = 0;
		img_num++;
	}
}

void	filter_panel_interaction_event(t_rt *rt_data, SDL_Event *event)
{
	if (event->button.x >= 0 && event->button.x <= 300
		&& event->button.y > SCR_SIZE - 430 && event->button.y <= SCR_SIZE - 350)
		rt_data->filter = GREYSCALE;
	else if (event->button.x >= 0 && event->button.x <= 300
			 && event->button.y > SCR_SIZE - 350 && event->button.y <= SCR_SIZE - 280)
		rt_data->filter = PIXEL;
	else if (event->button.x >= 0 && event->button.x <= 300
			 && event->button.y > SCR_SIZE - 280 && event->button.y <= SCR_SIZE - 200)
		rt_data->filter = SEPIA;
	else if (event->button.x >= 0 && event->button.x <= 300
			&& event->button.y > SCR_SIZE - 200 && event->button.y <= SCR_SIZE - 130)
		rt_data->filter = NEGATIVE;
}

void	create_gui(t_rt *rt_data, SDL_Event *event, int flag)
{
	if (flag == FOOT_GUI)
		foot_panel_interaction_event(rt_data, event);
	else if (flag == FIGURE_GUI)
		gui_interaction_event(rt_data, event);
	else if (flag == FILTER_GUI)
		filter_panel_interaction_event(rt_data, event);
}

int		check_if_in_gui(t_rt *rt_data, SDL_Event *event)
{
	if (event->button.x >= 0 && event->button.x <= 200
			&& event->button.y >= 0 && event->button.y <= 400)
		return (FIGURE_GUI);
	else if (rt_data->gui.filter_gui && event->button.x >= 0 && event->button.x <= 300
			&& event->button.y >= SCR_SIZE - 430 && event->button.y <= SCR_SIZE - 100)
		return (FILTER_GUI);
	else if (event->button.x >= 0 && event->button.x <= 700
			&& event->button.y >= SCR_SIZE - 100 && event->button.y <= SCR_SIZE)
		return (FOOT_GUI);
	else
		return (NO_GUI);
}

int		mouse_click_event(t_rt *rt_data, SDL_Event *event)
{
	t_ray		primary_ray;
	t_intersect	closest_inter;
	t_dot		pixel;
	int			i;

	pixel.x = event->button.x;
	pixel.y = event->button.y;
	primary_ray = compute_ray(rt_data->cl_data.camera, pixel);
	closest_inter = find_closest_inter(rt_data->cl_data, rt_data->objects_arr, primary_ray);
	i = 0;
	if (check_if_in_gui(rt_data, event) != NO_GUI)
		create_gui(rt_data, event, check_if_in_gui(rt_data, event));
	else
	{
		if (closest_inter.distance != INFINITY)
			while (i < rt_data->cl_data.num_of_objects)
			{
				if (closest_inter.fig->type != PLANE && closest_inter.fig == (rt_data->objects_arr + i)) {
					if (rt_data->objects_arr[i].is_cartoon)
						rt_data->objects_arr[i].is_cartoon = 0;
					else
						rt_data->objects_arr[i].is_cartoon = 1;
				}
				else
					rt_data->objects_arr[i].is_cartoon = 0;
				i++;
			}
	}
	draw_scene(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	return (0);
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
	else if (event->key.keysym.sym >= SDLK_KP_1 && event->key.keysym.sym <= SDLK_KP_0)
		manage_ellipsoid_axes(event->key.keysym.sym, rt_data);
	else
		return (0);
	draw_scene(rt_data);
//	cl_start(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	return (0);
}

int		check_camera_key(int keycode, int type_of_motion)
{
	if (type_of_motion == ROTATE)
	{
		if (keycode == SDLK_UP || keycode == SDLK_DOWN || keycode == SDLK_RIGHT ||
			keycode == SDLK_LEFT || keycode == SDLK_PAGEUP || keycode == SDLK_PAGEDOWN)
			return (TRUE);
		else
			return (FALSE);
	}
	else if (type_of_motion == SHIFT)
	{
		if (keycode == SDLK_w || keycode == SDLK_s || keycode == SDLK_d ||
			keycode == SDLK_a)
			return (TRUE);
		else
			return (FALSE);
	}
	else
		return (FALSE);
}