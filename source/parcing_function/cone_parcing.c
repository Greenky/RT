/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parcing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:42:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/07 12:42:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int				cone_parce(int fd, t_rt *rt_data)
{
	int			k;
	int			flag;
	char		*line;
	t_objects	*cone;

	flag = 0;
	cone = (t_objects *)malloc(sizeof(t_objects));
	cone->type = CONE;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
        cone_data_fill(&line, cone, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == CONE_IS_PARSED)// 15
			break ;
	}
	if (k < 0 || flag != CONE_IS_PARSED)
		error_exit(ERROR, NULL);
	cone->mirror_coef = 0;
	add_shape(rt_data, cone);
	return (0);
}

void		cone_data_fill(char **line, t_objects *cone, int line_number, int *flag)
{
	char		*new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		cone->origin = parce_vector(*line, line_number);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		cone->color = parce_color(*line, line_number);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "dir:"))
	{
		*line = trim_from(*line, 4);
		cone->basis.b_z = normalize_vector(parce_vector(*line, line_number));
		*flag = *flag | (1 << 2);
	}
	else
		more_cone_data_fill(line, cone, line_number, flag);
}

void		more_cone_data_fill(char **line, t_objects *cone, int line_number, int *flag)
{
	if (begin_with(*line, "ang:"))
	{
		*line = trim_from(*line, 4);
		cone->angle_coef = fminf(1, fmaxf(0.05, tanf(ANGLE_IN_DEGREES(str_to_float(*line, 0, line_number)))));
		*flag = *flag | (1 << 3);
	}
	else if (begin_with(*line, "b_p:"))
	{
		*line = trim_from(*line, 4);
		if ((cone->bling_phong = ft_atoi(*line)) <= 0)
			error_caster(line_number, "no such biling-phong coef. as ", *line);
		*flag = *flag | (1 << 4);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}
