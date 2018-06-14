/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:11:02 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/02 15:11:03 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static double	dest_to_plane(t_ray ray, t_plane *p)
{
	t_vector	v;
	double		znam;

	znam = scalar_dob(ray.direct, p->normal);
	if (!znam)
		return (MAX_LEN);
	v = sub_vectors(ray.origin, p->point);
	ray.dest = (-1) * scalar_dob(v, p->normal) / znam;
	if (ray.dest < 0)
		return (MAX_LEN);
	else
		return (ray.dest);
}

double			intersect_plane(t_ray *ray, void *pl, t_light *light,
t_shape *sh)
{
	t_vector	nor;
	t_ray		s_ray;
	t_plane		*p;
	int			color;

	p = (t_plane *)pl;
	color = 0;
	if (((*ray).dest = dest_to_plane(*ray, p)) == MAX_LEN)
		return (0);
	if (sh)
	{
		nor = v_to_len(p->normal, -1, 0);
		s_ray.id = p->id;
		s_ray.mirror = p->mirror;
		s_ray.main_col = p->color;
		s_ray.rev_dir = v_to_len((*ray).direct, -1, 1);
		s_ray.origin = add_vectors((*ray).origin, v_to_len((*ray).direct,
		(*ray).dest, 0));
		return (light_calculate(nor, s_ray, light, sh));
	}
	else
		return (1);
}

static void		plane_fill(char **line, t_plane *plane, int l_num, int *flag)
{
	char	*new_line;
	double	mirror;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		plane->point = parce_vector(*line, l_num);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		plane->color = parce_color(*line, l_num);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "nor:"))
	{
		*line = trim_from(*line, 4);
		plane->normal = v_to_len(parce_vector(*line, l_num), 1, 0);
		*flag = *flag | 4;
	}
	else if (begin_with(*line, "mir:"))
	{
		*line = trim_from(*line, 4);
		mirror = str_to_double(*line, 0, l_num);
		if (mirror > 1 || mirror < 0)
			error_caster(l_num, "no such mirror coef. as ", *line);
		if (mirror == 0)
			plane->mirror = 0;
		else
			plane->mirror = 1 / mirror;
		*flag = *flag | (1 << 3);
	}
	else
		error_caster(l_num, "no such parameter as ", *line);
}

int				plane_parce(int fd, int *l_num, void **shape_list, int id)
{
	int			k;
	int			flag;
	char		*line;
	t_plane		*plane;

	flag = 0;
	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->id = id;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(*l_num)++;
		plane_fill(&line, plane, *l_num, &flag);
		ft_strdel(&line);
		if (flag == 15)
			break ;
	}
	if (k < 0)
	{
		free(plane);
		perror("RTv1");
		exit(1);
	}
	add_shape((t_shape **)shape_list, plane, 'p', id);
	return (0);
}
