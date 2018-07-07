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

#include "rt_data.h"

double		distance_to_plane(t_ray ray, t_shape *plane)
{
	t_vector	v;
	double		znam;
	double		distance;

	znam = scalar_dob(ray.direct, plane->normal);
	if (!znam)
		return (MAX_LEN);
	v = sub_vectors(ray.origin, plane->origin);
	distance = (-1) * scalar_dob(v, plane->normal) / znam;
	if (distance < 0)
		return (MAX_LEN);
	else
		return (distance);
}

t_vector	normal_to_plane(t_ray ray, t_intersected intersected)
{
	ray.origin.x++; // usless line for Wall Wextra Werrror
	return(intersected.shape->normal);
}

static void		plane_fill(char **line, t_shape *plane, int line_number, int *flag)
{
	char	*buffer_line;
	double	mirror;

	buffer_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = buffer_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		plane->origin = parce_vector(*line, line_number);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		plane->color = parce_color(*line, line_number);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "nor:"))
	{
		*line = trim_from(*line, 4);
		plane->normal = v_to_len(parce_vector(*line, line_number), 1, 0);
		*flag = *flag | 4;
	}
	else if (begin_with(*line, "mir:"))
	{
		*line = trim_from(*line, 4);
		mirror = str_to_double(*line, 0, line_number);
		if (mirror > 1 || mirror < 0)
			error_caster(line_number, "no such mirror coef. as ", *line);
		if (mirror == 0)
			plane->mirror_coref = 0;
		else
			plane->mirror_coref = 1 / mirror;
		*flag = *flag | (1 << 3);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

int				plane_parce(int fd, t_rt *rt_data, int id)
{
	int			k;
	int			flag;
	char		*line;
	t_shape		*plane;

	flag = 0;
	plane = (t_shape *)malloc(sizeof(t_shape));
	plane->id = id;
	plane->name = PLANE;
	plane->find_distance = &distance_to_plane;
	plane->get_normal = &normal_to_plane;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		plane_fill(&line, plane, rt_data->line_number, &flag);
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
	add_shape(rt_data, plane);
	return (0);
}
