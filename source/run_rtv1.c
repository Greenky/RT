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

#include <time.h>
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

uint32_t	find_col_channel(float fig_color_channel, int step)
{
	uint32_t	mult;

	if (fig_color_channel < 0)
		return (0);
	mult = (uint32_t)(fig_color_channel) >> 8;
	if (mult > 0xFF)
		mult = 0xFF;
	return (mult << step);
}

uint32_t	rgb_to_int(t_channel rgb)
{
	int c = rgb.red;
	c = (c << 8) | rgb.green;
	c = (c << 8) | rgb.blue;
	return ((uint32_t)c);
}

void		ray_tracing(t_rt *rt_data)
{
	SDL_Event	event;

	SDL_Init(SDL_INIT_EVERYTHING);
	rt_data->cl_data.camera.initial_basis = rt_data->cl_data.camera.basis; // new
	rt_data->window = SDL_CreateWindow(W_TITLE, SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, SCR_SIZE,
								SCR_SIZE, SDL_WINDOW_ALLOW_HIGHDPI);
	rt_data->screen_surface = SDL_GetWindowSurface(rt_data->window);

	rt_data->cl_data.textures = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 20);
	load_texture(rt_data->cl_data.textures, 0, "textures/Earth_1024x512.bmp");
	load_texture(rt_data->cl_data.textures, 1, "textures/Brick_Wall.bmp");
	load_texture(rt_data->cl_data.textures, 2, "textures/Stonewall15_512x512.bmp");
	load_texture(rt_data->cl_data.textures, 3, "textures/Grass.bmp");
//	plasma_disruption(rt_data->cl_data.textures[2]);
//	perlin_noise_disruption(rt_data->cl_data.textures[1]);
	check_mate_disruption(rt_data->cl_data.textures[0]);
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

void 		load_texture(SDL_Surface **textures, int index, char *path)
{
	SDL_Surface *texture;
	if (!(texture = SDL_LoadBMP(path)))
	{
		printf("SDL_LoadBMP failed: %s\n", SDL_GetError());
		exit(1);
	}
	texture = SDL_ConvertSurfaceFormat(texture, SDL_PIXELFORMAT_ARGB8888, 0);
	textures[index] = texture;
}

void		get_texture(t_intersect *closest_inter, t_cl_data cl_data)
{
	cl_float3 nor;
	SDL_Surface *texture;

	float u;
	float v;
	int i;
	int j;

	if (closest_inter->distance == INFINITY)
	{
		closest_inter->texture_color = (t_channel) {0, 0, 0};
		return ;
	}
	nor = choose_normal(*closest_inter->fig, closest_inter->point);
	i = 0;
	j = 0;
	if (closest_inter->fig->texture_index != -1)
	{
		texture = cl_data.textures[closest_inter->fig->texture_index];
		if (closest_inter->fig->type == SPHERE)
		{
			u = acosf(nor.y);
			v = atan2f(nor.z, -nor.x);
			j = (int) (u * texture->h * M_1_PI);
			i = (int) (v * texture->w * M_1_PI / 2);
		}
		else if (closest_inter->fig->type == CYLINDER || closest_inter->fig->type == CONE)
		{
			v = atan2f(nor.z, -nor.x);
            if (closest_inter->fig->type == CONE)
            {
                u = length(vect_diff(closest_inter->fig->origin, closest_inter->point));
                u *= cosf(atanf(closest_inter->fig->angle_coef));
                closest_inter->fig->radius = u;
            }
			nor = vect_mult_scalar(nor, closest_inter->fig->radius);
			u = length(vect_diff(vect_sum(nor, closest_inter->point), closest_inter->fig->origin));
			i = (int)(v * texture->w * M_1_PI);
			j = (int)(u * 100) % texture->h;
		}
		else if (closest_inter->fig->type == PLANE)
		{
			nor = vect_diff(closest_inter->point, closest_inter->fig->origin);
			nor = matrix_mult_vect(closest_inter->fig->basis, nor);
			if (nor.x != 0)
			{
				i = (int) ((nor.x > 0 ? nor.x : texture->w + nor.x) * 100) % texture->w;
				j = (int) ((nor.y > 0 ? nor.y : texture->h + nor.y) * 100) % texture->h;
			}
			else
			{
				i = (int) ((nor.z > 0 ? nor.z : texture->w + nor.z) * 100) % texture->w;
				j = (int) ((nor.y > 0 ? nor.y : texture->h + nor.y) * 100) % texture->h;
			}
		}
//        i < 0 ?
		closest_inter->texture_color = int_to_channels(((unsigned int *) texture->pixels)[j * texture->w + i]);
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
	get_texture(&closest_inter, cl_data);
	return (closest_inter);
}
