/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_limited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 23:20:57 by vmazurok          #+#    #+#             */
/*   Updated: 2018/07/25 23:20:59 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

void parce_limited(char **line, t_objects *obj, int line_number)
{
	int i;
	if (begin_with(*line, "limited_top"))
	{
		*line = trim_from(*line, 11);
		obj->cap[0].normal = normalize_vector(parce_vector(*line, line_number));
		i = 0;
		while ((*line)[i] && (*line)[i] != ';')
			i++;
		*line = trim_from(*line, i + 1);
		obj->cap[0].dist = ft_atoi(*line);
	}
	else if (begin_with(*line, "limited_bottom"))
	{
		*line = trim_from(*line, 14);
		obj->cap[1].normal = normalize_vector(parce_vector(*line, line_number));
		i = 0;
		while ((*line)[i] && (*line)[i] != ';')
			i++;
		*line = trim_from(*line, i + 1);
		obj->cap[1].dist = ft_atoi(*line);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}