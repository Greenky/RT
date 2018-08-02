/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_parce.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 11:53:27 by vmazurok          #+#    #+#             */
/*   Updated: 2018/08/02 11:58:48 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int			triangle_parce(int fd, t_rt *rt_data)
{
	int			ret;
	int			flag;
	char		*line;
	t_objects	*triangle;

	flag = 0;
	triangle = (t_objects *)malloc(sizeof(t_objects));
	triangle->type = TRIANGLE;
	triangle->cap[0].dist = INFINITY;
	triangle->cap[1].dist = INFINITY;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		triang_data_fill(&line, triangle, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == TRIANGLE_IS_PARSED)
			break ;
	}
	if (ret < 0 || flag != TRIANGLE_IS_PARSED)
		error_exit(ERROR, NULL);
	add_obj_to_list(rt_data, triangle);
	return (0);
}

void		more_triang_data_fill3(char **line,
						t_objects *triangle, int line_number, int *flag)
{
	float	mirror;

	if (begin_with(*line, "texture index:"))
	{
		*line = trim_from(*line, 14);
		if ((triangle->texture_index = ft_atoi(*line)) < -4
			|| triangle->texture_index > 12)
			error_caster(line_number, "no such texture index. as ", *line);
		mirror = 0;
		while ((*line)[(int)mirror] && (*line)[(int)mirror] != ',')
			mirror++;
		*line = trim_from(*line, (int)mirror + 1);
		triangle->texture_repeat = (begin_with(*line, "repeat")
									? ft_atoi((*line) + 7) : 1);
		if (triangle->texture_repeat < 0)
			error_caster(line_number,
						"no such texture repeat number. as ", *line);
		*flag = *flag | (1 << 7);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

void		more_triang_data_fill2(char **line,
						t_objects *triangle, int line_number, int *flag)
{
	float	mirror;

	if (begin_with(*line, "b_p:"))
	{
		*line = trim_from(*line, 4);
		if ((triangle->bling_phong = ft_atoi(*line)) <= 0)
			error_caster(line_number, "no such biling-phong coef. as ", *line);
		*flag = *flag | (1 << 5);
	}
	else if (begin_with(*line, "trancper:"))
	{
		*line = trim_from(*line, 9);
		if ((mirror = str_to_float(*line, 0, line_number)) > 1 || mirror < 0)
			error_caster(line_number, "no such trancparency coef. as ", *line);
		triangle->transperent_coef = mirror;
		*flag = *flag | (1 << 6);
	}
	else
		more_triang_data_fill3(line, triangle, line_number, flag);
}

void		more_triang_data_fill(char **line,
							t_objects *triangle, int line_number, int *flag)
{
	if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		triangle->color = parce_color(*line, line_number);
		*flag = *flag | (1 << 2);
	}
	else if (begin_with(*line, "vertex2:"))
	{
		*line = trim_from(*line, 8);
		triangle->v1 = parce_vector(*line, line_number);
		*flag = *flag | (1 << 3);
	}
	else if (begin_with(*line, "vertex3:"))
	{
		*line = trim_from(*line, 8);
		triangle->v2 = parce_vector(*line, line_number);
		*flag = *flag | (1 << 4);
	}
	else
		more_triang_data_fill2(line, triangle, line_number, flag);
}

void		triang_data_fill(char **line,
							t_objects *triangle, int line_number, int *flag)
{
	char		*new_line;
	float		mirror;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "mir:"))
	{
		*line = trim_from(*line, 4);
		mirror = str_to_float(*line, 0, line_number);
		if (mirror > 1 || mirror < 0)
			error_caster(line_number, "no such mirror coef. as ", *line);
		triangle->mirror_coef = mirror;
		*flag = *flag | (1 << 0);
	}
	else if (begin_with(*line, "vertex1:"))
	{
		*line = trim_from(*line, 8);
		triangle->v0 = parce_vector(*line, line_number);
		*flag = *flag | (1 << 1);
	}
	else
		more_triang_data_fill(line, triangle, line_number, flag);
}
