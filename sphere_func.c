/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:13:23 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/01 18:13:24 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_functions.h"

static double		dest_to_sphere(t_ray ray, t_shape *sphere, t_rt *rt_data)
{
	t_vector	v1;
	double		descr;
	double		t[2];
	double		a_b_c[3];
	double		distance;
	
	v1 = sub_vectors(ray.origin, sphere->origin);
	a_b_c[0] = scalar_dob(ray.direct, ray.direct);
	a_b_c[1] = 2 * scalar_dob(ray.direct, v1);
	a_b_c[2] = scalar_dob(v1, v1) - sphere->radius * sphere->radius;
	descr = a_b_c[1] * a_b_c[1] - 4 * a_b_c[0] * a_b_c[2];
	if (descr <= 0)
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

double				intersect_sphere(t_ray *ray, t_shape *sphere, t_rt *rt_data)
{
	t_vector	nor;
	t_sphere	*s;
	t_ray		s_ray;
	int			color;

	s = (t_sphere *)sf;
	color = 0;
	if (((*ray).dest = dest_to_sphere(*ray, s)) == MAX_LEN)
		return (0);
	if (rt_data)
	{
		s_ray.origin = add_vectors((*ray).origin, v_to_len((*ray).direct,
		(*ray).dest, 0));
		s_ray.id = s->id;
		s_ray.main_col = s->color;
		s_ray.mirror = s->mirror;
		s_ray.transperent = s->transperent;
		s_ray.rev_dir = v_to_len((*ray).direct, -1, 1);
		nor = v_to_len(sub_vectors(s_ray.origin, s->centre), 1, 0);
		return (light_calculate(nor, s_ray, rt_data));
	}
	else
		return (1);
}

static void			sphere_fill(char **line, t_shape *sphere, int l_num, int *flag)
{
	char	*new_line;
	double	mirror;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		sphere->origin = parce_vector(*line, l_num);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		sphere->color = parce_color(*line, l_num);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "rad:"))
	{
		*line = trim_from(*line, 4);
		sphere->radius = fmax(1, str_to_double(*line, 0, l_num));
		*flag = *flag | 4;
	}
	else if (begin_with(*line, "mir:"))
	{
		*line = trim_from(*line, 4);
		mirror = str_to_double(*line, 0, l_num);
		if (mirror > 1 || mirror < 0)
			error_caster(l_num, "no such mirror coef. as ", *line);
		if (mirror == 0)
			sphere->mirror = 0;
		else
			sphere->mirror = 1 / mirror;
		*flag = *flag | (1 << 3);
	}
	else
		error_caster(l_num, "no such parameter as ", *line);
}

int					sphere_parce(int fd, t_rt *rt_data, int id)
{
	int			k;
	int			flag;
	char		*line;
	t_shape		*sphere;

	flag = 0;
	sphere = (t_shape *)malloc(sizeof(t_sphere));
	sphere->id = id;
	sphere->find_intersection = &intersect_sphere;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(rt_data->l_num)++;
		sphere_fill(&line, sphere, rt_data->l_num, &flag);
		ft_strdel(&line);
		if (flag == 15)
			break ;
	}
	if (k < 0 || flag != 15)
	{
		free(sphere);
		perror("RT");
		exit(1);
	}
	add_shape(rt_data, sphere);
	return (0);
}
