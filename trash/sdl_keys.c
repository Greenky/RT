/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:35:39 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/24 20:35:41 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_functions.h"

//int			exit_x(t_rt *rt_data, SDL_Event *event)
//{
//	if (event->type == SDL_QUIT
//		|| (event->type == SDL_KEYDOWN &&
//			event->key.keysym.scancode == SDL_SCANCODE_ESCAPE))
//	{
//		SDL_FreeSurface(rt_data->screen_surface);
//		SDL_DestroyWindow(rt_data->window);
//		SDL_Quit();
//		return (0);
//	}
//	else
//		return (1);
//}
//
//int			w_a_s_d_keys_down(t_rt *rt_data, SDL_Event *event)
//{
//	if (event->key.keysym.sym == SDLK_w)
//		rt_data->cl_data.camera.origin =
//				vect_diff(rt_data->cl_data.camera.origin,
//						vect_mult_scalar(rt_data->cl_data.camera.basis.b_z,
//							SHIFT_STEP));
//	else if (event->key.keysym.sym == SDLK_s)
//		rt_data->cl_data.camera.origin =
//				vect_sum(rt_data->cl_data.camera.origin,
//						vect_mult_scalar(rt_data->cl_data.camera.basis.b_z,
//							SHIFT_STEP));
//	else if (event->key.keysym.sym == SDLK_d)
//		rt_data->cl_data.camera.origin =
//				vect_sum(rt_data->cl_data.camera.origin,
//						vect_mult_scalar(rt_data->cl_data.camera.basis.b_x,
//							SHIFT_STEP));
//	else if (event->key.keysym.sym == SDLK_a)
//		rt_data->cl_data.camera.origin =
//				vect_diff(rt_data->cl_data.camera.origin,
//						vect_mult_scalar(rt_data->cl_data.camera.basis.b_x,
//							SHIFT_STEP));
//	else
//		return (FALSE);
//	return (TRUE);
//}
//
//int			key_down(t_rt *rt_data, SDL_Event *event)
//{
//	if (w_a_s_d_keys_down(rt_data, event))
//		;
//	else if (event->key.keysym.sym == SDLK_UP ||
//			event->key.keysym.sym == SDLK_DOWN ||
//			event->key.keysym.sym == SDLK_RIGHT ||
//			event->key.keysym.sym == SDLK_LEFT ||
//			event->key.keysym.sym == SDLK_PAGEUP ||
//			event->key.keysym.sym == SDLK_PAGEDOWN)
//		rotating_camera(event->key.keysym.sym, rt_data);
//	else if (event->key.keysym.sym == SDLK_SPACE)
//	{
//		rt_data->cl_data.camera.basis = rt_data->cl_data.camera.initial_basis;
//		rt_data->cl_data.camera.origin = VEC(0, 0, -20);
//		rt_data->cl_data.camera.angle_rot = VEC(0, 0, 0);
//	}
//	else if (event->key.keysym.sym == SDLK_7)
//		rt_data->objects->axis_dimensions.y -= 0.1;
//	else if (event->key.keysym.sym == SDLK_8)
//		rt_data->objects->axis_dimensions.y += 0.1;
//	else
//		return (0);
//	draw_scene(rt_data);
//	SDL_UpdateWindowSurface(rt_data->window);
//	return (0);
//}
//
//void		rotating_camera(int keycode, t_rt *rt_data)
//{
//	double		angle;
//
//	angle = (keycode == SDLK_UP || keycode == SDLK_RIGHT ||
//			keycode == SDLK_PAGEDOWN) ? ANGLE : -ANGLE;
//	if (keycode == SDLK_UP || keycode == SDLK_DOWN)
//		rt_data->cl_data.camera.angle_rot.x += angle;
//	else if (keycode == SDLK_RIGHT || keycode == SDLK_LEFT)
//		rt_data->cl_data.camera.angle_rot.y -= angle;
//	else
//		rt_data->cl_data.camera.angle_rot.z += angle;
//	rt_data->cl_data.camera.basis = init_basis_after_rot(rt_data);
//}
