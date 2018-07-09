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

#include "../inc/rtv1.h"

void		event_management(t_scene_data *scene, SDL_Event *event)
{
	int		running;

	running = 1;
	SDL_UpdateWindowSurface(scene->window);
	while (running)
	{
		while (SDL_PollEvent(event))
		{
			if (!exit_x(scene, event))
				running = 0;
			else if (event->type == SDL_KEYDOWN)
				key_down(scene, event);
		}
	}
}

int			exit_x(t_scene_data *scene, SDL_Event *event)
{
	if (event->type == SDL_QUIT
		|| (event->type == SDL_KEYDOWN &&
		event->key.keysym.scancode == SDL_SCANCODE_ESCAPE))
	{
		ft_lstdel(&(scene->lights), &free);
		ft_lstdel(&(scene->lights), &free);
		SDL_FreeSurface(scene->screen_surface);
		SDL_DestroyWindow(scene->window);
		SDL_Quit();
		return (0);
	}
	else
		return (1);
}

int			key_down(t_scene_data *scene, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_w)
		scene->camera.origin.z += 0.2;
	else if (event->key.keysym.sym == SDLK_s)
		scene->camera.origin.z -= 0.2;
	else if (event->key.keysym.sym == SDLK_d)
		scene->camera.origin.x += 0.2;
	else if (event->key.keysym.sym == SDLK_a)
		scene->camera.origin.x -= 0.2;
	else if (event->key.keysym.sym == SDLK_UP ||
		event->key.keysym.sym == SDLK_DOWN ||
		event->key.keysym.sym == SDLK_RIGHT ||
		event->key.keysym.sym == SDLK_LEFT ||
		event->key.keysym.sym == SDLK_PAGEUP ||
		event->key.keysym.sym == SDLK_PAGEDOWN)
		rotating_camera(event->key.keysym.sym, scene);
	else if (event->key.keysym.sym == SDLK_SPACE)
		init_standart_coord_sys(&(scene->camera.basis));
	else
		return (0);
	draw_all_scene(scene);
	SDL_UpdateWindowSurface(scene->window);
	return (0);
}

void		rotating_camera(int keycode, t_scene_data *scene)
{
	t_coord_sys	s;
	double		angle;
	t_coord_sys	rot_matrix;

	angle = (keycode == SDLK_UP || keycode == SDLK_RIGHT ||
			keycode == SDLK_PAGEDOWN) ? ANGLE : -ANGLE;
	s = scene->camera.basis;
	rot_matrix = init_rot_matrix(keycode, angle);
	if (keycode == SDLK_UP || keycode == SDLK_DOWN)
	{
		s.b_y = matrice_mult_vect(rot_matrix, scene->camera.basis.b_y);
		s.b_z = matrice_mult_vect(rot_matrix, scene->camera.basis.b_z);
	}
	else if (keycode == SDLK_RIGHT || keycode == SDLK_LEFT)
	{
		s.b_x = matrice_mult_vect(rot_matrix, scene->camera.basis.b_x);
		s.b_z = matrice_mult_vect(rot_matrix, scene->camera.basis.b_z);
	}
	else if (keycode == SDLK_PAGEUP || keycode == SDLK_PAGEDOWN)
	{
		s.b_x = matrice_mult_vect(rot_matrix, scene->camera.basis.b_x);
		s.b_y = matrice_mult_vect(rot_matrix, scene->camera.basis.b_y);
	}
	normalize_basis(&s);
	scene->camera.basis = s;
}

t_coord_sys	init_rot_matrix(int keycode, double angle)
{
	t_coord_sys	rot_matrix;

	if (keycode == SDLK_UP || keycode == SDLK_DOWN)
	{
		rot_matrix = (t_coord_sys){VEC(1, 0, 0), VEC(0, (float)cos(angle),
			(float)sin(angle)), VEC(0, -(float)sin(angle), (float)cos(angle))};
	}
	else if (keycode == SDLK_RIGHT || keycode == SDLK_LEFT)
	{
		rot_matrix = (t_coord_sys){VEC((float)cos(angle), 0,
			(float)-sin(angle)),
			VEC(0, 1, 0), VEC((float)sin(angle), 0, (float)cos(angle))};
	}
	else
	{
		rot_matrix = (t_coord_sys){VEC((float)cos(angle), (float)sin(angle), 0),
				VEC((float)-sin(angle), (float)cos(angle), 0), VEC(0, 0, 1)};
	}
	return (rot_matrix);
}
