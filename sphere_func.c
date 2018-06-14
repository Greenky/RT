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

#include "gfx.h"

static double		dest_to_phere(t_ray ray, t_sphere *s)
{
	t_vector	v1;
	double		descr;
	double		t[2];
	double		a_b_c[3];

	v1 = sub_vectors(ray.origin, s->centre);
	a_b_c[0] = scalar_dob(ray.direct, ray.direct);
	a_b_c[1] = 2 * scalar_dob(ray.direct, v1);
	a_b_c[2] = scalar_dob(v1, v1) - s->radius * s->radius;
	descr = a_b_c[1] * a_b_c[1] - 4 * a_b_c[0] * a_b_c[2];
	if (descr <= 0)
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

double				intersect_sphere(t_ray *ray, void *sf, t_light *light,
t_shape *sh)
{
	t_vector	nor;
	t_sphere	*s;
	t_ray		s_ray;
	int			color;

	s = (t_sphere *)sf;
	color = 0;
	if (((*ray).dest = dest_to_phere(*ray, s)) == MAX_LEN)
		return (0);
	if (sh)
	{
		s_ray.origin = add_vectors((*ray).origin, v_to_len((*ray).direct,
		(*ray).dest, 0));
		s_ray.id = s->id;
		s_ray.main_col = s->color;
		s_ray.mirror = s->mirror;
		s_ray.rev_dir = v_to_len((*ray).direct, -1, 1);
		nor = v_to_len(sub_vectors(s_ray.origin, s->centre), 1, 0);
		return (light_calculate(nor, s_ray, light, sh));
	}
	else
		return (1);
}

static void			sphere_fill(char **line, t_sphere *s, int l_num, int *flag)
{
	char	*new_line;
	double	mirror;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		s->centre = parce_vector(*line, l_num);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		s->color = parce_color(*line, l_num);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "rad:"))
	{
		*line = trim_from(*line, 4);
		s->radius = fmax(1, str_to_double(*line, 0, l_num));
		*flag = *flag | 4;
	}
	else if (begin_with(*line, "mir:"))
	{
		*line = trim_from(*line, 4);
		mirror = str_to_double(*line, 0, l_num);
		if (mirror > 1 || mirror < 0)
			error_caster(l_num, "no such mirror coef. as ", *line);
		if (mirror == 0)
			s->mirror = 0;
		else
			s->mirror = 1 / mirror;
		*flag = *flag | (1 << 3);
	}
	else
		error_caster(l_num, "no such parameter as ", *line);
}

int					sphere_parce(int fd, int *l_num, void **shape_list, int id)
{
	int			k;
	int			flag;
	char		*line;
	t_sphere	*sphere;

	flag = 0;
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->id = id;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(*l_num)++;
		sphere_fill(&line, sphere, *l_num, &flag);
		ft_strdel(&line);
		if (flag == 15)
			break ;
	}
	if (k < 0 || flag != 15)
	{
		free(sphere);
		perror("RTv1");
		exit(1);
	}
	add_shape((t_shape **)shape_list, sphere, 's', id);
	return (0);
}
