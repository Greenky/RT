/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylin_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:55:10 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/02 13:55:11 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static double	dest_to_cylin(t_ray ray, t_cylinder *cyl)
{
	t_vector	x;
	double		descr;
	double		a_b_c[3];
	double		t[2];

	ray.direct = v_to_len(ray.direct, 1, 0);
	x = sub_vectors(ray.origin, cyl->point);
	t[0] = scalar_dob(ray.direct, cyl->direct);
	t[1] = scalar_dob(x, cyl->direct);
	a_b_c[0] = scalar_dob(ray.direct, ray.direct) - (t[0] * t[0]);
	a_b_c[1] = 2 * (scalar_dob(ray.direct, x) - t[0] * t[1]);
	a_b_c[2] = scalar_dob(x, x) - (t[1] * t[1]) - cyl->radius * cyl->radius;
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

double			intersect_cylinder(t_ray *ray, void *cy, t_light *light,
t_shape *sh)
{
	t_ray		s_ray;
	t_vector	nor;
	double		m;
	t_cylinder	*cyl;

	cyl = (t_cylinder *)cy;
	if (((*ray).dest = dest_to_cylin(*ray, cyl)) == MAX_LEN)
		return (0);
	if (sh)
	{
		s_ray.origin = add_vectors((*ray).origin, v_to_len((*ray).direct,
		(*ray).dest, 0));
		s_ray.id = cyl->id;
		s_ray.main_col = cyl->color;
		s_ray.mirror = cyl->mirror;
		s_ray.rev_dir = v_to_len((*ray).direct, -1, 0);
		nor = add_vectors((*ray).origin, v_to_len((*ray).direct, (*ray).dest,
		0));
		m = scalar_dob((*ray).direct, v_to_len(cyl->direct, (*ray).dest, 0)) +
		scalar_dob(nor, cyl->direct);
		nor = sub_vectors(nor, cyl->point);
		nor = v_to_len(sub_vectors(nor, v_to_len(cyl->direct, m, 0)), 1, 0);
		return (light_calculate(nor, s_ray, light, sh));
	}
	else
		return (1);
}

static	void	more_fill(char **line, t_cylinder *cyl, int l_num, int *flag)
{
	if (begin_with(*line, "rad:"))
	{
		*line = trim_from(*line, 4);
		cyl->radius = fmax(1, str_to_double(*line, 0, l_num));
		*flag = *flag | (1 << 3);
	}
	else
		error_caster(l_num, "no such parameter as ", *line);
}

static void		cylin_fill(char **line, t_cylinder *cyl, int l_num, int *flag)
{
	char		*new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		cyl->point = parce_vector(*line, l_num);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		cyl->color = parce_color(*line, l_num);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "dir:"))
	{
		*line = trim_from(*line, 4);
		cyl->direct = v_to_len(parce_vector(*line, l_num), 1, 0);
		*flag = *flag | (1 << 2);
	}
	else
		more_fill(line, cyl, l_num, flag);
}

int				cylin_parce(int fd, int *l_num, void **shape_list, int id)
{
	int			k;
	int			flag;
	char		*line;
	t_cylinder	*cyl;

	flag = 0;
	cyl = (t_cylinder *)malloc(sizeof(t_cylinder));
	cyl->id = id;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(*l_num)++;
		cylin_fill(&line, cyl, *l_num, &flag);
		ft_strdel(&line);
		if (flag == 15)
			break ;
	}
	if (k < 0)
	{
		perror("RTv1");
		exit(1);
	}
	cyl->mirror = 0;
	add_shape((t_shape **)shape_list, cyl, 0, id);
	return (0);
}
