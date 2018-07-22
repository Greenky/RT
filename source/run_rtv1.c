/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_rtv1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 18:00:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:58:59 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void		choose_intersection(t_ray primary_ray, t_intersect *tmp_inter)
{
	if (tmp_inter->fig->type == SPHERE)
		sphere_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == CYLINDER)
		cyl_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == CONE)
		cone_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == PLANE)
		plane_find_closest_intersect(primary_ray, tmp_inter);
}

void		ray_tracing(t_rt *rt_data)
{
	SDL_Event	event;
	SDL_Surface *wall;

	SDL_Init(SDL_INIT_EVERYTHING);
//	rt_data->camera.initial_basis = rt_data->camera.basis;// old
	rt_data->cl_data.camera.initial_basis = rt_data->cl_data.camera.basis; // new
	rt_data->window = SDL_CreateWindow(W_TITLE, SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, SCR_SIZE,
								SCR_SIZE, SDL_WINDOW_ALLOW_HIGHDPI);
	rt_data->screen_surface = SDL_GetWindowSurface(rt_data->window);

	if (!(wall = SDL_LoadBMP("textures/Stonewall15_512x512.bmp")))
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		exit(1);
	}
	wall = SDL_ConvertSurfaceFormat(wall, SDL_PIXELFORMAT_ARGB8888, 0);
	rt_data->cl_data.texture = (unsigned int *)wall->pixels;

	draw_scene(rt_data);
//	draw_bar(rt_data);
//	text_output(rt_data);
//	draw_clicked_info(rt_data);
//	cl_start(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	event_management(rt_data, &event);
//	system("leaks RT");
}

t_ray		compute_ray(t_camera camera, t_dot pixel)
{
	t_ray	r;
	float	vertical;
	float	horizontal;

	r.origin = camera.origin;
	vertical = (float)((TOP_BOUND + pixel.y) * STEP);
	horizontal = (float)((LEFT_BOUND + pixel.x) * STEP);
	r.direction = normalize_vector(matrix_mult_vect(camera.basis,
													VEC(horizontal, -vertical, -DISTANCE)));
	return (r);
}



void		get_texture(t_intersect *closest_inter, unsigned int *texture)
{
	cl_float3 nor;

	nor = normalize_vector(vect_diff(closest_inter->point, closest_inter->fig->origin));
	float ro = acosf(-nor.z);
	float fi = atan2f(nor.y, nor.x);
	int i;
	int j;
	if (closest_inter->fig->texture_index == 0)
	{
		j = (int)(ro * 512 * M_1_PI);
		i = (int)(fi * 512 * M_1_PI / 2);
		closest_inter->texture_color = int_to_channels(texture[j * 512 + i]);
	}
	else
	{
		closest_inter->texture_color =  closest_inter->fig->color;
	}
}

t_intersect	find_closest_inter(t_cl_data cl_data, t_objects *objects, t_ray primary_ray)
{
	t_intersect	tmp_inter;
	t_intersect	closest_inter;
	int current;

	closest_inter.distance = INFINITY;
	current = 0;
	while (current < cl_data.num_of_objects)
	{
		tmp_inter.fig = &objects[current];
		choose_intersection(primary_ray, &tmp_inter);
		if (tmp_inter.distance < closest_inter.distance)
			closest_inter = tmp_inter;
		current++;
	}
	get_texture(&closest_inter, cl_data.texture);
	return (closest_inter);
}
