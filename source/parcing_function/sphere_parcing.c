/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parcing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:41:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/07 12:41:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int					sphere_parce(int fd, t_rt *rt_data)
{
	int			ret;
	int			flag;
	char		*line;
	t_objects	*sphere;

	flag = 0;
	sphere = (t_objects *)malloc(sizeof(t_objects));
	sphere->type = SPHERE;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		sphere_fill(&line, sphere, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == SPHERE_IS_PARSED)
			break ;
	}
	if (ret < 0 || flag != SPHERE_IS_PARSED)
	{
		free(sphere);
		error_exit(ERROR, NULL);
	}
	sphere->basis.b_z = VEC(0, 0, 1);
	add_shape(rt_data, sphere);
	return (0);
}

void			sphere_fill(char **line, t_objects *sphere, int line_number, int *flag)
{
	char	*new_line;
//	float	mirror;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		sphere->origin = parce_vector(*line, line_number);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		sphere->color = parce_color(*line, line_number);
		*flag = *flag | 2;
	}
	else if (begin_with(*line, "rad:"))
	{
		*line = trim_from(*line, 4);
		sphere->radius = (float)fmax(1, str_to_float(*line, 0, line_number));
		*flag = *flag | 4;
	}
//	else if (begin_with(*line, "mir:"))
//	{
//		*line = trim_from(*line, 4);
//		mirror = str_to_float(*line, 0, line_number);
//		if (mirror > 1 || mirror < 0)
//			error_caster(line_number, "no such mirror coef. as ", *line);
//		if (mirror == 0)
//			sphere->mirror_coef = 0;
//		else
//			sphere->mirror_coef = 1 / mirror;
//		*flag = *flag | (1 << 3);
//	}
	else if (begin_with(*line, "b_p:"))
	{
		*line = trim_from(*line, 4);
		if ((sphere->bling_phong = ft_atoi(*line)) <= 0)
			error_caster(line_number, "no such biling-phong coef. as ", *line);
		*flag = *flag | (1 << 3);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}
