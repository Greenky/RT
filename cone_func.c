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

#include "rt_functions.h"

double			distance_to_cone(t_ray ray, t_shape *cone)
{
	t_vector	v;
	double		descr;
	double		distance;
	double		a_b_c[3];
	double		t[2];

	v = sub_vectors(ray.origin, cone->origin);
	t[0] = scalar_dob(ray.direct, cone->direct);
	t[1] = scalar_dob(v, cone->direct);
	a_b_c[2] = (1 + cone->angle_coef * cone->angle_coef);
	a_b_c[0] = scalar_dob(ray.direct, ray.direct) - a_b_c[2] * (t[0] * t[0]);
	a_b_c[1] = 2 * (scalar_dob(ray.direct, v) - a_b_c[2] * t[0] * t[1]);
	a_b_c[2] = scalar_dob(v, v) - a_b_c[2] * (t[1] * t[1]);
	descr = a_b_c[1] * a_b_c[1] - 4 * a_b_c[0] * a_b_c[2];
	if (descr < 0)
		return (MAX_LEN);
	descr = sqrt(descr);
	t[0] = (-a_b_c[1] - descr) / (2 * a_b_c[0]);
	t[1] = (-a_b_c[1] + descr) / (2 * a_b_c[0]);
	distance = (t[0] < t[1]) ? t[0] : t[1];
	if (distance < 0)
		return (MAX_LEN);
	else
		return (distance);
}

t_vector		normal_to_cone(t_ray ray, t_intersected intersected)
{
	t_vector buffer_vector;
	t_vector normal;
	t_shape *cone;
	double	usless_coeficient;
	double	usefull_coeficient;

	cone = intersected.shape;
	buffer_vector = sub_vectors(ray.origin, intersected.shape->origin);
	usless_coeficient = scalar_dob(ray.direct, cone->direct) * (intersected.distance) +
	scalar_dob(buffer_vector, cone->direct);
	usefull_coeficient = (1 + cone->angle_coef * cone->angle_coef) * usless_coeficient;
	normal = sub_vectors(sub_vectors(intersected.intersect_point, cone->origin),
	v_to_len(cone->direct, usefull_coeficient, 0));
	return (v_to_len(normal, 1, 0));
}

static void		more_fill(char **line, t_shape *cone, int line_number, int *flag)
{
	if (begin_with(*line, "ang:"))
	{
		*line = trim_from(*line, 4);
		cone->angle_coef = fmin(1, fmax(0.05, tan(str_to_double(*line, 0, line_number) *
		M_PI / 180)));
		*flag = *flag | (1 << 3);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

static void		cone_fill(char **line, t_shape *cone, int line_number, int *flag)
{
	char		*new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		cone->origin = parce_vector(*line, line_number);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		cone->color = parce_color(*line, line_number);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "dir:"))
	{
		*line = trim_from(*line, 4);
		cone->direct = v_to_len(parce_vector(*line, line_number), 1, 0);
		*flag = *flag | (1 << 2);
	}
	else
		more_fill(line, cone, line_number, flag);
}

int				cone_parce(int fd, t_rt *rt_data, int id)
{
	int			k;
	int			flag;
	char		*line;
	t_shape		*cone;

	flag = 0;
	cone = (t_shape *)malloc(sizeof(t_shape));
	cone->id = id;
	cone->name = CONE;
	cone->find_distance = &distance_to_cone;
	cone->get_normal = &normal_to_cone;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		cone_fill(&line, cone, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == 15)
			break ;
	}
	if (k < 0)
	{
		perror("RT");
		exit(1);
	}
	cone->mirror_coef = 0;
	add_shape(rt_data, cone);
	return (0);
}
