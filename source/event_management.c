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


int mouse_click_event(t_rt *rt_data, SDL_Event *event)
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
	if (closest_inter.distance != INFINITY)
		while (i < rt_data->cl_data.num_of_objects)
		{
			if (closest_inter.fig == (rt_data->objects_arr + i)) {
				if (rt_data->objects_arr[i].is_cartoon)
					rt_data->objects_arr[i].is_cartoon = 0;
				else
					rt_data->objects_arr[i].is_cartoon = 1;
			}
			else
				rt_data->objects_arr[i].is_cartoon = 0;
			i++;
		}
	draw_scene(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	return (0);
}


void		event_management(t_rt *rt_data, SDL_Event *event)
{
	int		running;
	cl_float3	res;

	running = 1;
	SDL_UpdateWindowSurface(rt_data->window);
	res.x = 0;
	res.y = 0;
	res.z = 0;
	rt_data->cl_data.camera.angle_rot = res; // new
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
	if (event->key.keysym.sym == SDLK_w)
	{
		rt_data->cl_data.camera.origin =
				vect_diff(rt_data->cl_data.camera.origin,
						  vect_mult_scalar(rt_data->cl_data.camera.basis.b_z, SHIFT_STEP)); // new
	}
	else if (event->key.keysym.sym == SDLK_s)
	{
		rt_data->cl_data.camera.origin =
				vect_sum(rt_data->cl_data.camera.origin,
						 vect_mult_scalar(rt_data->cl_data.camera.basis.b_z, SHIFT_STEP)); // new
	}
	else if (event->key.keysym.sym == SDLK_d)
	{
		rt_data->cl_data.camera.origin =
				vect_sum(rt_data->cl_data.camera.origin,
						 vect_mult_scalar(rt_data->cl_data.camera.basis.b_x, SHIFT_STEP)); // new
	}
	else if (event->key.keysym.sym == SDLK_a)
	{
		rt_data->cl_data.camera.origin =
				vect_diff(rt_data->cl_data.camera.origin,
						  vect_mult_scalar(rt_data->cl_data.camera.basis.b_x, SHIFT_STEP)); // new
	}
	else if (event->key.keysym.sym == SDLK_UP ||
			 event->key.keysym.sym == SDLK_DOWN ||
			 event->key.keysym.sym == SDLK_RIGHT ||
			 event->key.keysym.sym == SDLK_LEFT ||
			 event->key.keysym.sym == SDLK_PAGEUP ||
			 event->key.keysym.sym == SDLK_PAGEDOWN)
		rotating_camera(event->key.keysym.sym, rt_data);
	else if (event->key.keysym.sym == SDLK_SPACE)
	{
		rt_data->cl_data.camera.basis = rt_data->cl_data.camera.initial_basis; // new
		rt_data->cl_data.camera.origin = VEC(0, 0, -20); // new
		rt_data->cl_data.camera.angle_rot = VEC(0, 0, 0); // new
	}
	else if (event->key.keysym.sym == SDLK_7)
	{
		//printf("type = %d\n", rt_data->objects->type);
		rt_data->objects->axis_dimensions.y -= 0.1;
		//handle_axis_dimensions(rt_data->objects);
	}
	else if (event->key.keysym.sym == SDLK_8)
	{
		rt_data->objects->axis_dimensions.y += 0.1;
		//handle_axis_dimensions(rt_data->objects);
	}
	else
		return (0);
	draw_scene(rt_data);
//	cl_start(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	return (0);
}

void		rotating_camera(int keycode, t_rt *rt_data)
{
	double		angle;

	angle = (keycode == SDLK_UP || keycode == SDLK_RIGHT ||
			keycode == SDLK_PAGEDOWN) ? ANGLE : -ANGLE;
	if (keycode == SDLK_UP || keycode == SDLK_DOWN)
	{
		rt_data->cl_data.camera.angle_rot.x += angle; // new
	}
	else if (keycode == SDLK_RIGHT || keycode == SDLK_LEFT)
	{
		rt_data->cl_data.camera.angle_rot.y -= angle; // new
	}
	else
	{
		rt_data->cl_data.camera.angle_rot.z += angle; // new
	}
//	printf("x = %f, y = %f, z = %f\n", rt_data->camera.angle_rot.x, rt_data->camera.angle_rot.y, rt_data->camera.angle_rot.z);//TODO delete
	rt_data->cl_data.camera.basis = init_basis_after_rot(rt_data); // new
}

t_coord_sys	init_basis_after_rot(t_rt *rt_data)
{
	t_coord_sys		new_basis;
	cl_float3		x_cam_sys;
	cl_float3		y_cam_sys;
	//cl_float3		z_cam_sys;

	new_basis = matrix_mult_matrix(rt_data->cl_data.camera.initial_basis,
								   rot_matrix_about_the_axis(rt_data->cl_data.camera.angle_rot.z, VEC(0, 0, 1))); // new
	y_cam_sys = matrix_mult_vect(count_inverse_matrix(new_basis), new_basis.b_y); // new
	new_basis = matrix_mult_matrix(new_basis,
								   rot_matrix_about_the_axis(rt_data->cl_data.camera.angle_rot.y, y_cam_sys)); // new
	x_cam_sys = matrix_mult_vect(count_inverse_matrix(new_basis), new_basis.b_x); // new
	new_basis = matrix_mult_matrix(new_basis,
								   (rot_matrix_about_the_axis(rt_data->cl_data.camera.angle_rot.x, x_cam_sys))); // new
	return (new_basis);
}

t_coord_sys		rot_matrix_about_the_axis(float angle, cl_float3 axis)
{
	t_coord_sys rot_matrix;

	rot_matrix.b_x.x = cosf(angle) + (1 - cosf(angle)) * find_square(axis.x);
	rot_matrix.b_y.x = (1 - cosf(angle)) * axis.x * axis.y - sinf(angle) * axis.z;
	rot_matrix.b_z.x = (1 - cosf(angle)) * axis.x * axis.z + sinf(angle) * axis.y;

	rot_matrix.b_x.y = (1 - cosf(angle)) * axis.y * axis.x + sinf(angle) * axis.z;
	rot_matrix.b_y.y = cosf(angle) + (1 - cosf(angle)) * find_square(axis.y);
	rot_matrix.b_z.y = (1 - cosf(angle)) * axis.y * axis.z - sinf(angle) * axis.x;

	rot_matrix.b_x.z = (1 - cosf(angle)) * axis.z * axis.x - sinf(angle) * axis.y;
	rot_matrix.b_y.z = (1 - cosf(angle)) * axis.z * axis.y + sinf(angle) * axis.x;
	rot_matrix.b_z.z = cosf(angle) + (1 - cosf(angle)) * find_square(axis.z);
	return (rot_matrix);
}


//------------------------------------------------------------------

//
//t_channel				int_to_channels(int col)
//{
//	t_channel channels;
//
//	channels.blue = col & 255;
//	channels.green = col >> 8 & 255;
//	channels.red = col >> 16 & 255;
//	return (channels);
//}
////
//t_intersect	find_closest_reflected_inter(t_cl_data cl_data,__constant t_objects *objects, t_ray ray, __constant t_objects *this)
//{
//t_intersect	tmp_inter;
//t_intersect	closest_inter;
//int current;
//
//closest_inter.distance = INFINITY;
//current = 0;
//while (current < cl_data.num_of_objects)
//{
//	tmp_inter.fig = &objects[current];
//	choose_intersection(ray, &tmp_inter);
//	if (tmp_inter.distance < closest_inter.distance && tmp_inter.fig != this)
//		closest_inter = tmp_inter;
//	current++;
//}
//return (closest_inter);
//}