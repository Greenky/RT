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
	return c;
}

//double	dist(double a, double c, double d, double d)
//{
//	return (sqrt(double((a - c) * (a - c) + (b - d) * (b - d))));
//}




inline double findnoise2(double x,double y)
{
	int n=(int)x+(int)y*57;
	n=(n<<13)^n;
	int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
	return 1.0-((double)nn/1073741824.0);
}


inline double interpolate(double a,double b,double x)
{
	double ft=x * 3.1415927;
	double f=(1.0-cos(ft))* 0.5;
	return a*(1.0-f)+b*f;
}

double noise(double x,double y)
{
	double floorx=(double)((int)x);
	double floory=(double)((int)y);
	double s,t,u,v;
	s=findnoise2(floorx,floory);
	t=findnoise2(floorx+1,floory);
	u=findnoise2(floorx,floory+1);
	v=findnoise2(floorx+1,floory+1);
	double int1=interpolate(s,t,x-floorx);
	double int2=interpolate(u,v,x-floorx);
	return interpolate(int1,int2,y-floory);
}

int		perlin_noise(int x, int y, double p, double zoom)
{
	int	octaves = 2;
	double getnoise = 0;
	t_channel	channel;
	for (int a = 0; a < octaves - 1; a++)
	{
		double	frequency = pow(2,a);
		double	amplitude = pow(p, a);
		getnoise += noise(((double)x)*frequency/zoom,((double)y)/zoom*frequency)*amplitude;
	}
	int color= (int)((getnoise*128.0)+128.0);
	if(color > 255)
		color = 255;
	if(color<0)
		color=0;
	channel = int_to_channels(color);
	channel.red = (int)((50.0 / 255.0) * (double)color);
	channel.green = (int)((100.0 / 255.0) * (double)color);
	channel.blue = (int)((150.0 / 255.0) * (double)color);
	color = rgb_to_int(channel);
	return (color);
}

void		perlin_noise_disruption(SDL_Surface *surface)
{
	int	y;
	int	x;
	int	color;

	color = 0;
	y = -1;
	while (++y < surface->h)
	{
		x = -1;
		while (++x < surface->w)
		{
			color = perlin_noise(x, y, 1/2, 4.2);
			set_pixel(surface, x, y, color);
		}
	}
}

void		check_mate_disruption(SDL_Surface *surface)
{
	int	i;
	int	j;
	int	color;

	color = 0;
	j = -1;
	while (++j < surface->h)
	{
		i = -1;
		if (j % 20 == 0)
			color = (color == 0) ? 0xFFFFFF : 0;
		while (++i < surface->w)
		{
			if (i % 20 == 0)
				color = (color == 0) ? 0xFFFFFF : 0;
			set_pixel(surface, i, j, color);
		}
	}
}

void		disrupt_texture(SDL_Surface *surface)
{
	int	i;
	int	j;
	int	color;
	t_channel	rgb;
	double time = clock() / 50.0;
//	int	paletteShift;

	j = -1;
	while (++j < surface->h)
	{
		i = -1;
		while (++i < surface->w)
		{
			double value = sin(dist(i + time, j, surface->h / 2, surface->h / 2) / 8.0)
						   + sin(dist(i, j, surface->h / 4, surface->w / 4) / 8.0)
						   + sin(dist(i, j + time / 7, (surface->w / 4 * 3), surface->w / 4) / 7.0)
						   + + sin(dist(i, j, (surface->w / 4 * 3), 100.0) / 8.0);
			color = (int)((4 + value)) * 32;
			rgb.red = color;
			rgb.green = color * 2;
			rgb.blue = 255 - color;
			set_pixel(surface, i, j, rgb_to_int(rgb));
		}
	}
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
	disrupt_texture(rt_data->cl_data.textures[2]);
	perlin_noise_disruption(rt_data->cl_data.textures[1]);
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
				i = (int) ((nor.x > 0 ? nor.x : -nor.x) * 100) % texture->w;
				j = (int) ((nor.y > 0 ? nor.y : -nor.y) * 100) % texture->h;
			}
			else
			{
				i = (int) ((nor.z > 0 ? nor.z : -nor.z) * 100) % texture->w;
				j = (int) ((nor.y > 0 ? nor.y : -nor.y) * 100) % texture->h;
			}
		}
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
