/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:41:17 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/05 16:41:18 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static int	lighter(t_vector nor, t_ray s_ray, t_light *light, t_vector h)
{
	int		col_b;
	int		col_g;
	int		col_r;
	double	nor_li;
	double	w;

	nor_li = scalar_dob(nor, s_ray.direct);
	w = fmax(0, scalar_dob(nor, h));
	w = pow(w, 100);
	// w = 0;
	col_b = fmin(0xFF, (light->color & 255) * fmax(0, nor_li) * light->intence
	+ (light->color & 255) * w * light->intence);
	col_g = fmin(0xFF, (light->color >> 8 & 255) * fmax(0, nor_li) *
	light->intence + (light->color >> 8 & 255) * w * light->intence);
	col_r = fmin(0xFF, (light->color >> 16 & 255) * fmax(0, nor_li) *
	light->intence + (light->color >> 16 & 255) * w * light->intence);
	return (col_b + (col_g * 256) + (col_r * 256 * 256));
}

static int	ambient_light(int shape_col, t_light *light)
{
	int		col_b;
	int		col_g;
	int		col_r;
	double	k;

	k = 0;
	while (light)
	{
		k = fmax(light->intence / 2, k);
		light = light->next;
	}
	col_b = fmax(0, (shape_col & 255) * k);
	col_g = fmax(0, (shape_col >> 8 & 255) * k);
	col_r = fmax(0, (shape_col >> 16 & 255) * k);
	return (col_b + (col_g * 256) + (col_r * 256 * 256));
}

int			color_add(int first, int second)
{
	int sum;

	sum = fmin(0xFF, (first & 255) + (second & 255));
	sum += fmin(0xFF, (first >> 8 & 255) + (second >> 8 & 255)) * 256;
	sum += fmin(0xFF, (first >> 16 & 255) + (second >> 16 & 255)) * 256 * 256;
	return (sum);
}

static int	not_in_the_shadow(t_ray s_ray, t_shape *sh, t_light *light)
{
	while (sh)
	{
		if ((sh->id != s_ray.id) && (sh->inter(&s_ray, sh->shape, light, NULL)))
		{
			if ((!light->is_dir && s_ray.dest < v_mod(sub_vectors(s_ray.origin,
			light->direct))) || light->is_dir)
				return (0);
		}
		sh = sh->next;
	}
	return (1);
}

int				zercal_light(t_vector r, t_ray ray, t_light *li, t_shape *sh)
{
	double		a;
	t_shape		*head;
	int			color;
	int			color_to_scene;
	double		min;

	head = sh;
	color = 0;
	a = 2 * scalar_dob(r, v_to_len(ray.rev_dir, -1, 0));
	r = v_to_len(r, a, 0);
	ray.direct = v_to_len(sub_vectors(v_to_len(ray.rev_dir, -1, 0), r), 1, 0);
	min = MAX_LEN;
	while (sh)
	{
		if (sh->id != ray.id)
		{
			color = sh->inter(&ray, sh->shape, li, head);
			if (ray.dest <= min)
			{
				min = ray.dest;
				color_to_scene = color;
			}
		}
		sh = sh->next;
	}
	color = color_to_scene;
	color = ((color & 255) / ray.mirror) + (((color >> 8 & 255) / ray.mirror)
	<< 8) + (((color >> 16 & 255) / ray.mirror) << 16);
	return(color);
}

int			light_calculate(t_vector nor, t_ray s_ray, t_light *light,
t_shape *sh)
{
	t_vector	h;
	int			color;

	color = ambient_light(s_ray.main_col, light);
	if (s_ray.mirror)
		color = color_add(color, zercal_light(nor, s_ray, light, sh));
	while (light)
	{
		if (light->is_dir)
			s_ray.direct = v_to_len(light->direct, -1, 0);
		else
			s_ray.direct = v_to_len(sub_vectors(light->direct, s_ray.origin),
			1, 0);
		if (not_in_the_shadow(s_ray, sh, light))
		{
			h = add_vectors(s_ray.rev_dir, s_ray.direct);
			color = color_add(color, lighter(nor, s_ray, light, v_to_len(h,
			1, 0)));
		}
		light = light->next;
	}
	return (color);
}
