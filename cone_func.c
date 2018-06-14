/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 20:54:05 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/01 20:54:06 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static double	dest_to_cone(t_ray ray, t_cone *cone)
{
	t_vector	v;
	double		descr;
	double		a_b_c[3];
	double		t[2];

	v = sub_vectors(ray.origin, cone->point);
	t[0] = scalar_dob(ray.direct, cone->direct);
	t[1] = scalar_dob(v, cone->direct);
	a_b_c[2] = (1 + cone->ang * cone->ang);
	a_b_c[0] = scalar_dob(ray.direct, ray.direct) - a_b_c[2] * (t[0] * t[0]);
	a_b_c[1] = 2 * (scalar_dob(ray.direct, v) - a_b_c[2] * t[0] * t[1]);
	a_b_c[2] = scalar_dob(v, v) - a_b_c[2] * (t[1] * t[1]);
	descr = a_b_c[1] * a_b_c[1] - 4 * a_b_c[0] * a_b_c[2];
	if (descr < 0)
		return (MAX_LEN);
	descr = sqrt(descr);
	t[0] = (-a_b_c[1] - descr) / (2 * a_b_c[0]);
	t[1] = (-a_b_c[1] + descr) / (2 * a_b_c[0]);
	ray.dest = (t[0] < t[1]) ? t[0] : t[1];
	if (ray.dest < 0)
		return (MAX_LEN);
	else
		return (ray.dest);
}

double			intersect_cone(t_ray *ray, void *con, t_light *light,
t_shape *sh)
{
	t_vector	nor;
	double		a;
	t_cone		*cone;
	t_ray		s_ray;

	cone = (t_cone *)con;
	if (((*ray).dest = dest_to_cone(*ray, cone)) == MAX_LEN)
		return (0);
	if (sh)
	{
		s_ray.origin = add_vectors((*ray).origin, v_to_len((*ray).direct,
		(*ray).dest, 0));
		s_ray.id = cone->id;
		s_ray.main_col = cone->color;
		s_ray.mirror = cone->mirror;
		s_ray.rev_dir = v_to_len((*ray).direct, -1, 1);
		nor = sub_vectors((*ray).origin, cone->point);
		a = scalar_dob((*ray).direct, cone->direct) * ((*ray).dest) +
		scalar_dob(nor, cone->direct);
		a = (1 + cone->ang * cone->ang) * a;
		nor = v_to_len(sub_vectors(sub_vectors(s_ray.origin, cone->point),
		v_to_len(cone->direct, a, 0)), 1, 0);
		return (light_calculate(nor, s_ray, light, sh));
	}
	else
		return (1);
}

static void		more_fill(char **line, t_cone *cone, int l_num, int *flag)
{
	if (begin_with(*line, "ang:"))
	{
		*line = trim_from(*line, 4);
		cone->ang = fmin(1, fmax(0.05, tan(str_to_double(*line, 0, l_num) *
		M_PI / 180)));
		*flag = *flag | (1 << 3);
	}
	else
		error_caster(l_num, "no such parameter as ", *line);
}

static void		cone_fill(char **line, t_cone *cone, int l_num, int *flag)
{
	char		*new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		cone->point = parce_vector(*line, l_num);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		cone->color = parce_color(*line, l_num);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "dir:"))
	{
		*line = trim_from(*line, 4);
		cone->direct = v_to_len(parce_vector(*line, l_num), 1, 0);
		*flag = *flag | (1 << 2);
	}
	else
		more_fill(line, cone, l_num, flag);
}

int				cone_parce(int fd, int *l_num, void **shape_list, int id)
{
	int			k;
	int			flag;
	char		*line;
	t_cone		*cone;

	flag = 0;
	cone = (t_cone *)malloc(sizeof(t_cone));
	cone->id = id;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(*l_num)++;
		cone_fill(&line, cone, *l_num, &flag);
		ft_strdel(&line);
		if (flag == 15)
			break ;
	}
	if (k < 0)
	{
		perror("RTv1");
		exit(1);
	}
	cone->mirror = 0;
	add_shape((t_shape **)shape_list, cone, 'c', id);
	return (0);
}
