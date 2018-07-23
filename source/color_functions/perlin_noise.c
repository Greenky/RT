/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 22:25:32 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 22:25:34 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

inline double	findnoise2(double x,double y)
{
	int	n;
	int	nn;

	n = (int)x + (int)y * 57;
	n = (n << 13)^n;
	nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return (1.0 - ((double)nn / 1073741824.0));
}

inline double	interpolate(double a,double b,double x)
{
	double ft;
	double f;

	ft = x * 3.1415927;
	f = (1.0 - cos(x * 3.1415927)) * 0.5;
	return (a * (1.0 - (1.0 - cos(x * 3.1415927)) * 0.5) + b * (1.0 - cos(x * 3.1415927)) * 0.5);
}

double			noise(double x,double y)
{
	double floorx;
	double floory;

	floorx = (double)((int)x);
	floory = (double)((int)y);
	return interpolate(
			interpolate(
					findnoise2(floorx,floory),
					findnoise2(floorx+1,floory),x-floorx),
			interpolate(
					findnoise2(floorx,floory+1),
					findnoise2(floorx+1,floory+1),x-floorx),y-floory);
}

int				perlin_noise(int x, int y, double p, double zoom)
{
	int			octaves;
	double		getnoise;
	t_channel	channel;
	int			a;

	octaves = 2;
	getnoise = 0;
	a = -1;
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
