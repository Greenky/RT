/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_parcing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 13:28:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/15 13:28:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int					ellipsoid_parce(int fd, t_rt *rt_data)//TODO check
{
	int			ret;
	int			flag;
	char		*line;
	t_objects	*ellipsoid;

	flag = 0;
	ellipsoid = (t_objects *)malloc(sizeof(t_objects));
	ellipsoid->type = ELLIPSOID;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		ellipsoid_fill(&line, ellipsoid, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == ELLIPSOID_IS_PARSED)//TODO add define for this
			break ;
	}
	if (ret < 0 || flag != ELLIPSOID_IS_PARSED)//TODO add define for this
	{
		free(ellipsoid);
		error_exit(ERROR, NULL);
	}
	ellipsoid->basis.b_z = VEC(0, 0, 1);
	ellipsoid->radius = find_biggest_axis(ellipsoid);
	handle_axis_dimensions(ellipsoid);
	add_shape(rt_data, ellipsoid);
	return (0);
}

void			ellipsoid_fill(char **line, t_objects *ellipsoid, int line_number, int *flag)//TODO check
{
	char	*new_line;
//	float	mirror;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		ellipsoid->origin = parce_vector(*line, line_number);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		ellipsoid->color = parce_color(*line, line_number);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "axis sizes:"))
	{
		*line = trim_from(*line, 11);
		ellipsoid->axis_dimensions = parce_vector(*line, line_number);
		*flag = *flag | 4;//TODO check
	}

//	else if (begin_with(*line, "mir:"))
//	{
//		*line = trim_from(*line, 4);
//		mirror = str_to_float(*line, 0, line_number);
//		if (mirror > 1 || mirror < 0)
//			error_caster(line_number, "no such mirror coef. as ", *line);
//		if (mirror == 0)
//			ellipsoid->mirror_coef = 0;
//		else
//			ellipsoid->mirror_coef = 1 / mirror;
//		*flag = *flag | (1 << 3);
//	}
	else if (begin_with(*line, "b_p:"))
	{
		*line = trim_from(*line, 4);
		if ((ellipsoid->specular_coef = ft_atoi(*line)) <= 0)
			error_caster(line_number, "no such specular coef. as ", *line);
		*flag = *flag | (1 << 3);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}
