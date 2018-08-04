/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:36:59 by vmazurok          #+#    #+#             */
/*   Updated: 2018/08/02 16:22:00 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

static void		find_texture_color(t_intersect *closest, t_cl_data cl_data,
							SDL_Surface *texture, t_dot pixel)
{
	t_channel	normal_channel;

	if (closest->fig->texture_index < 10)
		closest->texture_color = int_to_channels(((int *)texture->pixels)[
		(pixel.y % texture->h) * texture->w + (pixel.x % texture->w)]);
	else if (closest->fig->texture_index == 10)
		closest->texture_color =
				int_to_channels(check_mate_disruption(pixel.y, pixel.x));
	else if (closest->fig->texture_index == 11)
		closest->texture_color =
				int_to_channels(plasma_disruption(pixel.y, pixel.x));
	else if (closest->fig->texture_index == 12)
		closest->texture_color =
				int_to_channels(perlin_noise_disruption(pixel.y, pixel.x));
	if (closest->fig->texture_index == 5 || closest->fig->texture_index == 6)
	{
		texture = cl_data.textures[closest->fig->texture_index + 5];
		normal_channel = int_to_channels(((int *)texture->pixels)[
		(pixel.y % texture->h) * texture->w + (pixel.x % texture->w)]);
		closest->normal = normalize_vector(VEC(normal_channel.red - 128,
		normal_channel.green - 128, normal_channel.blue - 128));
	}
}

static t_dot	plane_mapping(t_intersect *closest, cl_float3 nor)
{
	float		u;
	float		v;
	t_dot		pixel;
	cl_float3	buf_u;
	cl_float3	buf_v;

	buf_u = vect_cross_product(nor, VEC(0.f, 1.f, 0.f));
	if (fabsf(length(buf_u)) < 0.0001f)
		buf_u = vect_cross_product(nor, VEC(0.f, 0.f, 1.f));
	buf_v = vect_cross_product(nor, buf_u);
	u = vect_scalar_mult(buf_u, closest->point) + 5;
	v = vect_scalar_mult(buf_v, closest->point) + 5;
	u = u < 0 ? -u : u;
	v = v < 0 ? -v : v;
	pixel.x = (int)(50 * u * closest->fig->texture_repeat);
	pixel.y = (int)(50 * v * closest->fig->texture_repeat);
	return (pixel);
}

static t_dot	cylindric_mapping(t_intersect *closest, cl_float3 nor,
int h, int w)
{
	float		u;
	float		v;
	t_dot		pixel;

	(void)h;
	v = atan2f(nor.z, -nor.x);
	if (closest->fig->type == CONE)
	{
		u = length(vect_diff(closest->fig->origin, closest->point));
		u *= cosf(atanf(closest->fig->angle_coef));
		closest->fig->radius = u;
	}
	nor = vect_mult_scalar(nor, closest->fig->radius);
	u = length(vect_diff(vect_sum(nor, closest->point), closest->fig->origin));
	pixel.x = (int)(v * w * M_1_PI * closest->fig->texture_repeat);
	pixel.y = (int)(u * 100 * closest->fig->texture_repeat);
	return (pixel);
}

static t_dot	spherical_mapping(t_intersect *closest, cl_float3 nor,
int h, int w)
{
	float		u;
	float		v;
	t_dot		pixel;

	nor = matrix_mult_vect(closest->fig->basis, nor);
	u = acosf(-nor.y);
	v = atan2f(nor.z, -nor.x);
	pixel.y = (int)(u * h * M_1_PI * closest->fig->texture_repeat);
	pixel.x = (int)(v * w * M_1_PI / 2 * closest->fig->texture_repeat);
	return (pixel);
}

void			texture_mapping(t_intersect *closest_inter, t_cl_data cl_data,
cl_float3 nor, SDL_Surface *texture)
{
	t_dot	pixel;
	int		h;
	int		w;

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
	pixel.y = 0;
	pixel.x = 0;
	if (closest_inter->fig->type == SPHERE
		|| closest_inter->fig->type == ELLIPSOID)
		pixel = spherical_mapping(closest_inter, nor, h, w);
	else if (closest_inter->fig->type == CYLINDER ||
			closest_inter->fig->type == CONE)
		pixel = cylindric_mapping(closest_inter, nor, h, w);
	else if (closest_inter->fig->type == PLANE ||
			closest_inter->fig->type == TRIANGLE)
		pixel = plane_mapping(closest_inter, nor);
	find_texture_color(closest_inter, cl_data, texture, pixel);
}
