/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_rt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 18:00:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/01 21:51:56 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void		run_rt(t_rt *rt_data)
{
	SDL_Event	event;
	int			i;
	const char	*textures[] = {"textures/Earth_1024x512.bmp",
"textures/Brick_Wall.bmp", "textures/Stonewall15_512x512.bmp",
"textures/Grass.bmp", "textures/spoody_man.bmp", "textures/floor_tiles.bmp",
"textures/Stone_02_COLOR.bmp", "textures/Floor_Wdn.bmp",
"textures/metallplates.bmp", "textures/camo.bmp",
"textures/floor_tiles_NRM.bmp", "textures/Stone_02_NRM.bmp"};

	SDL_Init(SDL_INIT_EVERYTHING);
	rt_data->cl_data.camera.initial_basis = rt_data->cl_data.camera.basis;
	rt_data->window = SDL_CreateWindow(W_TITLE, SDL_WINDOWPOS_UNDEFINED,
										SDL_WINDOWPOS_UNDEFINED, WIN_SIZE,
										WIN_SIZE, SDL_WINDOW_ALLOW_HIGHDPI);
	rt_data->screen_surface = SDL_GetWindowSurface(rt_data->window);
	rt_data->cl_data.textures =
			(SDL_Surface **)malloc(sizeof(SDL_Surface *) * 20);
	i = -1;
	while (++i < 12)
		load_texture(rt_data->cl_data.textures, i, textures[i]);
	rt_data->aliasing = 1;
	draw_scene(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	event_management(rt_data, &event);
}

t_ray		compute_ray(t_camera camera, t_dot pixel, int antialias)
{
	t_ray	r;
	float	vertical;
	float	horizontal;

	r.origin = camera.origin;
	vertical = (float)((TOP_BOUND + (float)pixel.y / antialias) * STEP);
	horizontal = (float)((LEFT_BOUND + (float)pixel.x / antialias) * STEP);
	r.direction = normalize_vector(matrix_mult_vect(camera.basis,
						VEC(horizontal, -vertical, -DISTANCE)));
	return (r);
}

void		load_texture(SDL_Surface **textures, int index,
const char *path)
{
	SDL_Surface *texture;
	SDL_Surface	*new_text;

	if (!(texture = SDL_LoadBMP(path)))
	{
		ft_putendl_fd(SDL_GetError(), 2);
		exit(1);
	}
	new_text = SDL_ConvertSurfaceFormat(texture, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(texture);
	textures[index] = new_text;
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

t_intersect	find_closest_inter(t_cl_data cl_data, t_objects *objs, t_ray ray)
{
	t_intersect	tmp_inter;
	t_intersect	closest_inter;
	int			current;

	closest_inter.distance = INFINITY;
	current = 0;
	while (current < cl_data.num_of_objects)
	{
		tmp_inter.fig = &objs[current];
		choose_intersection(ray, &tmp_inter);
		if (tmp_inter.distance < closest_inter.distance)
			closest_inter = tmp_inter;
		current++;
	}
	get_texture(&closest_inter, cl_data);
	return (closest_inter);
}
