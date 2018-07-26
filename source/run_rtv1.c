/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_rtv1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 18:00:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/26 19:37:54 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "../includes/rt_functions.h"

static const char 		*g_textures[] = {
		"textures/Earth_1024x512.bmp",
		"textures/Brick_Wall.bmp",
		"textures/Stonewall15_512x512.bmp",
		"textures/Grass.bmp",
		"textures/spoody_man.bmp",
		"textures/floor_tiles.bmp",
		"textures/Stone_02_COLOR.bmp",
		"textures/Floor_Wdn.bmp",
		"textures/metallplates.bmp",
		"textures/camo.bmp",
		"textures/floor_tiles_NRM.bmp",
		"textures/Stone_02_NRM.bmp"
};

void		run_rt(t_rt *rt_data)
{
	SDL_Event	event;
	int 		i;

	SDL_Init(SDL_INIT_EVERYTHING);
	rt_data->cl_data.camera.initial_basis = rt_data->cl_data.camera.basis; // new
	rt_data->window = SDL_CreateWindow(W_TITLE, SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, SCR_SIZE,
								SCR_SIZE, SDL_WINDOW_ALLOW_HIGHDPI);
	rt_data->screen_surface = SDL_GetWindowSurface(rt_data->window);
	rt_data->cl_data.textures = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 20);
	i = -1;
	while (++i < 12)
		load_texture(rt_data->cl_data.textures, i, g_textures[i]);

//	plasma_disruption(rt_data->cl_data.textures[10]);
//	perlin_noise_disruption(rt_data->cl_data.textures[11]);
//	check_mate_disruption(rt_data->cl_data.textures[12]);

	draw_scene(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	event_management(rt_data, &event);
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

void 		load_texture(SDL_Surface **textures, int index, const char *path)
{
	SDL_Surface *texture;
	SDL_Surface	*new_text;
	if (!(texture = SDL_LoadBMP(path)))
	{
		ft_putendl_fd(SDL_GetError(), 2);
		exit(1);//TODO fix this
	}
	new_text = SDL_ConvertSurfaceFormat(texture, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(texture);
	textures[index] = new_text;
}

//void		color_disraption_mapping(t_intersect *closest_inter, t_cl_data cl_data, cl_float3 nor)
//{
//  TODO зробити
//}

void		texture_mapping(t_intersect *closest_inter, t_cl_data cl_data,
							cl_float3 nor, SDL_Surface *texture)
{
	t_channel	normal_channel;
	float		u;
	float		v;
	int			i;
	int			j;

	int h;
	int w;

	if (closest_inter->fig->texture_index < 10)
	{
		h = texture->h;
		w = texture->w;
	}
	else
	{
		h = 2000;
		w = 2000;
	}
//	if (closest_inter->fig->texture_index > 9) TODO зробити
//	{
//		color_disraption_mapping(closest_inter, cl_data, nor);
//	}
	i = 0;
	j = 0;
	if (closest_inter->fig->type == SPHERE
		|| closest_inter->fig->type == ELLIPSOID)
	{
		nor = matrix_mult_vect(closest_inter->fig->basis, nor);
		u = acosf(-nor.y);
		v = atan2f(nor.z, -nor.x);
		j = (int) (u * h * M_1_PI * closest_inter->fig->texture_repeat);
		i = (int) (v * w * M_1_PI / 2 * closest_inter->fig->texture_repeat);
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
		i = (int)(v * w * M_1_PI * closest_inter->fig->texture_repeat);
		j = (int)(u * 100 * closest_inter->fig->texture_repeat);
	}
	else if (closest_inter->fig->type == PLANE)
	{
		nor = vect_diff(closest_inter->point, closest_inter->fig->origin);
		nor = matrix_mult_vect(closest_inter->fig->basis, nor);
		if (nor.x != 0)
		{
			i = (int) ((nor.x > 0 ? nor.x : w + nor.x) * 50 * closest_inter->fig->texture_repeat);
			j = (int) ((nor.y > 0 ? nor.y : h + nor.y) * 50 * closest_inter->fig->texture_repeat);
		}
		else
		{
			i = (int) ((nor.z > 0 ? nor.z : w + nor.z ) * 50 * closest_inter->fig->texture_repeat);
			j = (int) ((nor.x > 0 ? nor.y : h + nor.y) * 50 * closest_inter->fig->texture_repeat);
		}
	}
	if (closest_inter->fig->texture_index < 10)
		closest_inter->texture_color = int_to_channels(((unsigned int *) texture->pixels)[(j % h) * w + (i % w)]);
	else if (closest_inter->fig->texture_index == 10)
		closest_inter->texture_color = int_to_channels(check_mate_disruption(j, i));
	else if (closest_inter->fig->texture_index == 11)
		closest_inter->texture_color = int_to_channels(plasma_disruption(j, i));
	else if (closest_inter->fig->texture_index == 12)
		closest_inter->texture_color = int_to_channels(perlin_noise_disruption(j, i));

	if (closest_inter->fig->texture_index == 5 || closest_inter->fig->texture_index == 6)
	{
		texture = cl_data.textures[closest_inter->fig->texture_index + 5];
		normal_channel = int_to_channels(((unsigned int *) texture->pixels)[(j % h) * w + (i % w)]);
		closest_inter->normal = normalize_vector(VEC(normal_channel.red - 128, normal_channel.green - 128, normal_channel.blue - 128));
	}
}

void		get_texture(t_intersect *closest_inter, t_cl_data cl_data)
{
	cl_float3	nor;
	SDL_Surface *texture;

	if (closest_inter->distance == INFINITY)
	{
		closest_inter->texture_color = (t_channel) {0, 0, 0};
		return ;
	}
	nor = choose_normal(*closest_inter->fig, closest_inter->point);
	if (closest_inter->fig->texture_index != -1)
	{
		texture = cl_data.textures[closest_inter->fig->texture_index];
		texture_mapping(closest_inter, cl_data, nor, texture);
	}
	else
		closest_inter->texture_color = closest_inter->fig->color;
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
