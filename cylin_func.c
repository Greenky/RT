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

#include "rt_functions.h"

double			distance_to_cylinder(t_ray ray, t_shape *cylinder)
{
	t_vector	x;
	double		descr;
	double		distance;
	double		a_b_c[3];
	double		t[2];

	ray.direct = v_to_len(ray.direct, 1, 0);
	x = sub_vectors(ray.origin, cylinder->origin);
	t[0] = scalar_dob(ray.direct, cylinder->direct);
	t[1] = scalar_dob(x, cylinder->direct);
	a_b_c[0] = scalar_dob(ray.direct, ray.direct) - (t[0] * t[0]);
	a_b_c[1] = 2 * (scalar_dob(ray.direct, x) - t[0] * t[1]);
	a_b_c[2] = scalar_dob(x, x) - (t[1] * t[1]) - cylinder->radius * cylinder->radius;
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

t_vector		normal_to_cylinder(t_ray ray, t_intersected intersected)
{
	t_vector	buffer_vector;
	t_vector	normal;
	double		usfull_coeficient;
	t_shape		*cylinder;
	
	cylinder = intersected.shape;
	usfull_coeficient = scalar_dob(ray.direct, v_to_len(cylinder->direct, intersected.distance, 0)) +
	scalar_dob(intersected.intersect_point, cylinder->direct);
	buffer_vector = sub_vectors(intersected.intersect_point, cylinder->origin);
	normal = sub_vectors(buffer_vector, v_to_len(cylinder->direct, usfull_coeficient, 0));
	return (v_to_len(normal, -1, 0));
}

static	void	more_fill(char **line, t_shape *cylinder, int line_number, int *flag)
{
	if (begin_with(*line, "rad:"))
	{
		*line = trim_from(*line, 4);
		cylinder->radius = fmax(1, str_to_double(*line, 0, line_number));
		*flag = *flag | (1 << 3);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

static void		cylin_fill(char **line, t_shape *cylinder, int line_number, int *flag)
{
	char		*new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		cylinder->origin = parce_vector(*line, line_number);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		cylinder->color = parce_color(*line, line_number);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "dir:"))
	{
		*line = trim_from(*line, 4);
		cylinder->direct = v_to_len(parce_vector(*line, line_number), 1, 0);
		*flag = *flag | (1 << 2);
	}
	else
		more_fill(line, cylinder, line_number, flag);
}

int				cylin_parce(int fd, t_rt *rt_data, int id)
{
	int			k;
	int			flag;
	char		*line;
	t_shape		*cylinder;

	flag = 0;
	cylinder = (t_shape *)malloc(sizeof(t_shape));
	cylinder->id = id;
	cylinder->name = CYLINDER;
	cylinder->find_distance = &distance_to_cylinder;
	cylinder->get_normal = &normal_to_cylinder;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		cylin_fill(&line, cylinder, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == 15)
			break ;
	}
	if (k < 0)
	{
		perror("RT");
		exit(1);
	}
	cylinder->mirror_coef = 0;
	add_shape(rt_data, cylinder);
	return (0);
}
