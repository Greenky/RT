/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 14:31:48 by vmazurok          #+#    #+#             */
/*   Updated: 2018/04/27 14:31:49 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void		pixel_add(t_grafx *gfx, int x, int y, unsigned int color)
{
	int bpp;
	int size_l;
	int end;
	int *buff;

	if (x >= 0 && x < SCR_SIZE && y >= 0 && y < SCR_SIZE)
	{
		buff = (int *)mlx_get_data_addr(gfx->img, &bpp, &size_l, &end);
		buff[SCR_SIZE * y + x] = color;
	}
}

int			find_color_for_me_pleas(t_ray ray, t_shape *sh, t_light *light)
{
	double	min;
	int		color;
	int		color_to_scene;
	t_shape	*head;

	head = sh;
	color_to_scene = 0;
	min = MAX_LEN;
	while (sh)
	{
		color = sh->inter(&ray, sh->shape, light, head);
		if (ray.dest <= min)
		{
			min = ray.dest;
			color_to_scene = color;
		}
		sh = sh->next;
	}
	return (color_to_scene);
}

void		ray_casting(t_grafx *gfx, t_shape *shape_list, t_light *light,
t_camera camera)
{
	double		i;
	double		j;
	t_ray		ray;
	t_vector	v[3];
	int			color;

	j = (-1) * SCR_SIZE / 2;
	camera.direct = v_to_len(camera.direct, camera.dest, 1);
	ray.origin = camera.origin;
	while (j < SCR_SIZE / 2)
	{
		i = (-1) * SCR_SIZE / 2;
		while (i < SCR_SIZE / 2)
		{
			v[0] = v_to_len(camera.up, j, 1);
			v[1] = v_to_len(camera.right, i, 1);
			v[2] = add_vectors(v[0], v[1]);
			ray.direct = v_to_len(add_vectors(v[2], camera.direct), 1, 0);
			color = find_color_for_me_pleas(ray, shape_list, light);
			pixel_add(gfx, i + 500, j + 500, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(gfx->mlx, gfx->win, gfx->img, 0, 0);
}

void		add_shape(t_shape **sh, void *shape, char name, int id)
{
	t_shape	*step;
	t_shape	*last;

	last = (t_shape *)malloc(sizeof(t_shape));
	last->name = name;
	last->id = id;
	last->shape = shape;
	if (name == 's')
		last->inter = &intersect_sphere;
	else if (name == 'p')
		last->inter = &intersect_plane;
	else if (name == 'c')
		last->inter = &intersect_cone;
	else
		last->inter = &intersect_cylinder;
	last->next = NULL;
	step = *sh;
	if (step)
	{
		while (step->next)
			step = step->next;
		step->next = last;
	}
	else
		*sh = last;
}
