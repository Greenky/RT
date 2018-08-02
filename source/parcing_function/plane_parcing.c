/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parcing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:41:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/31 21:49:35 by vmazurok         ###   ########.fr       */
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
	plane->transperent_coef = 0;
	plane->cap[0].dist = INFINITY;
	plane->cap[1].dist = INFINITY;
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
	add_obj_to_list(rt_data, plane);
	return (0);
}

static void	even_more_plane_fill(char **line,
							t_objects *plane, int line_number, int *flag)
{
	float	mirror;

	plane->type = PLANE;
	if (begin_with(*line, "texture index:"))
	{
		*line = trim_from(*line, 14);
		if ((plane->texture_index = ft_atoi(*line)) < -1
			|| plane->texture_index > 12)
			error_caster(line_number, "no such texture index. as ", *line);
		mirror = 0;
		while ((*line)[(int)mirror] && (*line)[(int)mirror] != ',')
			mirror++;
		*line = trim_from(*line, (int)mirror + 1);
		plane->texture_repeat = (begin_with(*line, "repeat")
								? ft_atoi((*line) + 7) : 1);
		if (plane->texture_repeat <= 0)
			error_caster(line_number,
						"no such texture repeat number. as ", *line);
		*flag = *flag | (1 << 5);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
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
		even_more_plane_fill(line, plane, line_number, flag);
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
