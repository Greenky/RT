/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_limited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 23:20:57 by vmazurok          #+#    #+#             */
/*   Updated: 2018/07/31 21:54:23 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

inline void	more_limited(char **line, t_objects *obj, int line_number,
						int *flag)
{
	int i;

	i = 0;
	if (begin_with(*line, "limited_bottom:"))
	{
		*line = trim_from(*line, 15);
		obj->cap[1].normal = normalize_vector(parce_vector(*line, line_number));
		while ((*line)[i] && (*line)[i] != ';')
			i++;
		*line = trim_from(*line, i + 1);
		obj->cap[1].dist = str_to_float(*line, 0, line_number);
		*flag = *flag | (1 << 9);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

void		parce_limited(char **line, t_objects *obj, int line_number,
						int *flag)
{
	int i;

	i = 0;
	if (begin_with(*line, "limited: -"))
		*flag = *flag | (1 << 8) | (1 << 9);
	else if (begin_with(*line, "limited_top:"))
	{
		*line = trim_from(*line, 12);
		obj->cap[0].normal = normalize_vector(parce_vector(*line, line_number));
		while ((*line)[i] && (*line)[i] != ';')
			i++;
		*line = trim_from(*line, i + 1);
		obj->cap[0].dist = str_to_float(*line, 0, line_number);
		*flag = *flag | (1 << 8);
	}
	else
		more_limited(line, obj, line_number, flag);
}
