/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parcing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:41:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/07 12:41:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int			plane_parce(int fd, t_rt *rt_data)
{
	int			ret;
	int			flag;
	char		*line;
	t_objects	*plane;

	flag = 0;
	plane = (t_objects *)malloc(sizeof(t_objects));
	plane->type = PLANE;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		plane_fill(&line, plane, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == PLANE_IS_PARSED)
			break ;
	}
	if (ret < 0 || flag != PLANE_IS_PARSED)
	{
		free(plane);
		error_exit(ERROR, NULL);
	}
	add_shape(rt_data, plane);
	return (0);
}

static void	more_plane_fill(char **line,
							t_objects *plane, int line_number, int *flag)
{
	if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		plane->color = parce_color(*line, line_number);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "nor:"))
	{
		*line = trim_from(*line, 4);
		plane->normal = normalize_vector(parce_vector(*line, line_number));
		plane->basis.b_z = plane->normal;
		*flag = *flag | 4;
	}
	else if (begin_with(*line, "b_p:"))
	{
		*line = trim_from(*line, 4);
		if ((plane->bling_phong = ft_atoi(*line)) <= 0)
			error_caster(line_number, "no such biling-phong coef. as ", *line);
		*flag = *flag | (1 << 4);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

void		plane_fill(char **line,
					t_objects *plane, int line_number, int *flag)
{
	char	*buffer_line;
	float	mirror;

	buffer_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = buffer_line;
	if (begin_with(*line, "mir:"))
	{
		*line = trim_from(*line, 4);
		mirror = str_to_float(*line, 0, line_number);
		if (mirror > 1 || mirror < 0)
			error_caster(line_number, "no such mirror coef. as ", *line);
		plane->mirror_coef = mirror;
		*flag = *flag | (1 << 3);
	}
	else if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		plane->origin = parce_vector(*line, line_number);
		*flag = *flag | 1;
	}
	else
		more_plane_fill(line, plane, line_number, flag);
}
