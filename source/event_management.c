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

#include "../includes/rt_functions.h"

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

int			key_down(t_rt *rt_data, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_w)
		rt_data->camera.origin =
				vect_diff(rt_data->camera.origin,
				vect_mult(rt_data->camera.basis.b_z, 0.1));
	else if (event->key.keysym.sym == SDLK_s)
		rt_data->camera.origin =
				vect_sum(rt_data->camera.origin,
				vect_mult(rt_data->camera.basis.b_z, 0.1));
	else if (event->key.keysym.sym == SDLK_d)
		rt_data->camera.origin =
				vect_sum(rt_data->camera.origin,
				vect_mult(rt_data->camera.basis.b_x, 0.1));
	else if (event->key.keysym.sym == SDLK_a)
		rt_data->camera.origin =
				vect_diff(rt_data->camera.origin,
				vect_mult(rt_data->camera.basis.b_x, 0.1));
	else if (event->key.keysym.sym == SDLK_UP ||
			 event->key.keysym.sym == SDLK_DOWN ||
			 event->key.keysym.sym == SDLK_RIGHT ||
			 event->key.keysym.sym == SDLK_LEFT ||
			 event->key.keysym.sym == SDLK_PAGEUP ||
			 event->key.keysym.sym == SDLK_PAGEDOWN)
		rotating_camera(event->key.keysym.sym, rt_data);
	else if (event->key.keysym.sym == SDLK_SPACE)
	{
		rt_data->camera.basis = rt_data->camera.initial_basis;
		rt_data->camera.origin = VEC(0, 0, 0);
	}
	else
		return (0);
	draw_scene(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	return (0);
}

void		rotating_camera(int keycode, t_rt *rt_data)
{
	t_coord_sys	s;
	double		angle;
	t_coord_sys	rot_matrix;

	angle = (keycode == SDLK_UP || keycode == SDLK_RIGHT ||
			 keycode == SDLK_PAGEDOWN) ? ANGLE : -ANGLE;
	s = rt_data->camera.initial_basis;
	rot_matrix = init_rot_matrix(rt_data, keycode, angle);
	s = matrix_mult_matrix(rt_data->camera.initial_basis, rot_matrix);
	rt_data->camera.basis = s;
}

t_coord_sys	init_rot_matrix(t_rt *rt_data, int keycode, double angle)
{
	t_coord_sys	rot_matrix;

	if (keycode == SDLK_UP || keycode == SDLK_DOWN)
		rt_data->camera.angle_rot.x += angle;
	else if (keycode == SDLK_RIGHT || keycode == SDLK_LEFT)
		rt_data->camera.angle_rot.y -= angle;
	else
		rt_data->camera.angle_rot.z += angle;

	rot_matrix.b_x.x = (float)(cos(rt_data->camera.angle_rot.y) *
							   cos(rt_data->camera.angle_rot.z));
	rot_matrix.b_x.y = (float)(sin(rt_data->camera.angle_rot.x) *
							   sin(rt_data->camera.angle_rot.y) * cos(rt_data->camera.angle_rot.z) +
							   cos(rt_data->camera.angle_rot.x) * sin(rt_data->camera.angle_rot.z));
	rot_matrix.b_x.z = (float)(-sin(rt_data->camera.angle_rot.y) *
							   cos(rt_data->camera.angle_rot.x) * cos(rt_data->camera.angle_rot.z) +
							   sin(rt_data->camera.angle_rot.x) * sin(rt_data->camera.angle_rot.z));
	rot_matrix.b_y.x = (float)(-cos(rt_data->camera.angle_rot.y) *
							   sin(rt_data->camera.angle_rot.z));
	rot_matrix.b_y.y = (float)(cos(rt_data->camera.angle_rot.x) *
							   cos(rt_data->camera.angle_rot.z) - sin(rt_data->camera.angle_rot.x) *
																  sin(rt_data->camera.angle_rot.y) * sin(rt_data->camera.angle_rot.z));
	rot_matrix.b_y.z = (float)(sin(rt_data->camera.angle_rot.x) *
							   cos(rt_data->camera.angle_rot.z) + cos(rt_data->camera.angle_rot.x) *
																  sin(rt_data->camera.angle_rot.y) * sin(rt_data->camera.angle_rot.z));
	rot_matrix.b_z.x = (float)(sin(rt_data->camera.angle_rot.y));
	rot_matrix.b_z.y = (float)(-sin(rt_data->camera.angle_rot.x) *
							   cos(rt_data->camera.angle_rot.y));
	rot_matrix.b_z.z = (float)(cos(rt_data->camera.angle_rot.x) *
							   cos(rt_data->camera.angle_rot.y));
//	printf("rot_x = %f, rot_y = %f, rot_z = %f\n", rt_data->camera.angle_rot.x, rt_data->camera.angle_rot.y, rt_data->camera.angle_rot.z);
	return (rot_matrix);
}
