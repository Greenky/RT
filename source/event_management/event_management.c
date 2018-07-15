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
	int		running;

	running = 1;
	SDL_UpdateWindowSurface(rt_data->window);
	while (running)
	{
		while (SDL_PollEvent(event))
		{
			if (!exit_x(rt_data, event))
				running = 0;
			else if (event->type == SDL_KEYDOWN)
				key_down(rt_data, event);
		}
	}
}

int			exit_x(t_rt *rt_data, SDL_Event *event)
{
	if (event->type == SDL_QUIT
		|| (event->type == SDL_KEYDOWN &&
		event->key.keysym.scancode == SDL_SCANCODE_ESCAPE))
	{
		freesher(rt_data->lights, rt_data->objects);
		SDL_FreeSurface(rt_data->screen_surface);
		SDL_DestroyWindow(rt_data->window);
		SDL_Quit();
		return (0);
	}
	else
		return (1);
}

int			key_down(t_rt *rt_data, SDL_Event *event)//перенесла некоторыеусловия в новые ф-ции
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

void	manage_ellipsoid_axes(int keycode, t_rt *rt_data)
{
	t_objects	*fig;

	fig = &(rt_data->objects_arr[0]);
	/*while (fig && fig->type != SPHERE)//check selection ellipsoid
		fig = fig->next;//change when user interface will be
	if (fig == NULL)
		return;*/
	fig->axis_dimensions = vect_mult_scalar(fig->axis_dimensions, fig->radius);
	if (keycode == SDLK_KP_7)
		fig->axis_dimensions.x -= 0.1;
	else if (keycode == SDLK_KP_8)
		fig->axis_dimensions.x += 0.1;
	else if (keycode == SDLK_KP_4)
		fig->axis_dimensions.y -= 0.1;
	else if (keycode == SDLK_KP_5)
		fig->axis_dimensions.y += 0.1;
	else if (keycode == SDLK_KP_1)
		fig->axis_dimensions.z -= 0.1;
	else if (keycode == SDLK_KP_2)
		fig->axis_dimensions.z += 0.1;
	check_axis_dimensions(&fig->axis_dimensions.x);
	check_axis_dimensions(&fig->axis_dimensions.y);
	check_axis_dimensions(&fig->axis_dimensions.z);
	handle_axis_dimensions(fig);
	printf("axis_dimensions.x = %f, axis_dimensions.y = %f, axis_dimensions.z = %f\n",
		fig->axis_dimensions.x, fig->axis_dimensions.y, fig->axis_dimensions.z);//TODO delete
}



