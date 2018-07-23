/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parcing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:15:13 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 14:15:17 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int				cylinder_parce(int fd, t_rt *rt_data)
{
	int			ret;
	int			flag;
	char		*line;
	t_objects	*cylinder;

	flag = 0;
	cylinder = (t_objects *)malloc(sizeof(t_objects));
	cylinder->type = CYLINDER;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		cylin_data_fill(&line, cylinder, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == CYLINDER_IS_PARSED)
			break ;
	}
	if (ret < 0 || flag != CYLINDER_IS_PARSED)
		error_exit(ERROR, NULL);
	add_shape(rt_data, cylinder);
	return (0);
}

void			cylin_data_fill(char **line,
							t_objects *cylinder, int line_number, int *flag)
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
	else
		more_cylin_data_fill(line, cylinder, line_number, flag);
}

void			more_cylin_data_fill2(char **line,
						t_objects *cylinder, int line_number, int *flag)
{
	float	mirror;

	if (begin_with(*line, "mir:"))
	{
		*line = trim_from(*line, 4);
		mirror = str_to_float(*line, 0, line_number);
		if (mirror > 1 || mirror < 0)
			error_caster(line_number, "no such mirror coef. as ", *line);
		cylinder->mirror_coef = mirror;
		*flag = *flag | (1 << 5);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

void			more_cylin_data_fill(char **line,
							t_objects *cylinder, int line_number, int *flag)
{
	if (begin_with(*line, "rad:"))
	{
		*line = trim_from(*line, 4);
		cylinder->radius = (float)fmax(1, str_to_float(*line, 0, line_number));
		*flag = *flag | (1 << 3);
	}
	else if (begin_with(*line, "b_p:"))
	{
		*line = trim_from(*line, 4);
		if ((cylinder->bling_phong = ft_atoi(*line)) <= 0)
			error_caster(line_number, "no such biling-phong coef. as ", *line);
		*flag = *flag | (1 << 4);
	}
	else if (begin_with(*line, "dir:"))
	{
		*line = trim_from(*line, 4);
		cylinder->basis.b_z =
				normalize_vector(parce_vector(*line, line_number));
		*flag = *flag | (1 << 2);
	}
	else
		more_cylin_data_fill2(line, cylinder, line_number, flag);
}
