/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_parcing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:40:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/23 17:40:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int				ellipsoid_parce(int fd, t_rt *rt_data)
{
	int			ret;
	int			flag;
	char		*line;
	t_objects	*ellipsoid;

	flag = 0;
	ellipsoid = (t_objects *)malloc(sizeof(t_objects));
	ellipsoid->type = ELLIPSOID;
	while ((ret = get_next_line(fd, &line)) > 0 && (rt_data->line_number)++)
	{
		ellipsoid_fill(&line, ellipsoid, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == ELLIPSOID_IS_PARSED)
			break ;
	}
	if (ret < 0 || flag != ELLIPSOID_IS_PARSED)
	{
		free(ellipsoid);
		error_exit(ERROR, NULL);
	}
	ellipsoid->basis.b_z = VEC(0, 0, 1);
	ellipsoid->radius = find_biggest_axis(ellipsoid);
	handle_axis_dimensions(ellipsoid);
	add_obj_to_list(rt_data, ellipsoid);
	return (0);
}

void			ellipsoid_fill(char **line,
					t_objects *ellipsoid, int line_number, int *flag)
{
	char *new_line;

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
		*flag = *flag | (1 << 1);
	}
	else if (begin_with(*line, "axis sizes:"))
	{
		*line = trim_from(*line, 11);
		ellipsoid->axis_dimensions = parce_vector(*line, line_number);
		*flag = *flag | (1 << 2);
	}
	else
		more_ellipsoid_fill(line, ellipsoid, line_number, flag);
}

void			even_even_more_ellipsoid_fill(char **line,
					t_objects *ellipsoid, int line_number, int *flag)
{
	float	mirror;

	if (begin_with(*line, "texture index:"))
	{
		*line = trim_from(*line, 14);
		if ((ellipsoid->texture_index = ft_atoi(*line)) < -1
			|| ellipsoid->texture_index > 12)
			error_caster(line_number, "no such texture index. as ", *line);
		mirror = 0;
		while ((*line)[(int)mirror] && (*line)[(int)mirror] != ',')
			mirror++;
		*line = trim_from(*line, (int)mirror + 1);
		ellipsoid->texture_repeat =
			(begin_with(*line, "repeat") ? ft_atoi((*line) + 7) : 1);
		if (ellipsoid->texture_repeat < 0)
			error_caster(line_number,
					"no such texture repeat number. as ", *line);
		*flag = *flag | (1 << 6);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

void			even_more_ellipsoid_fill(char **line,
					t_objects *ellipsoid, int line_number, int *flag)
{
	float	mirror;

	if (begin_with(*line, "trancper:"))
	{
		*line = trim_from(*line, 9);
		mirror = str_to_float(*line, 0, line_number);
		if (mirror > 1 || mirror < 0)
			error_caster(line_number, "no such trancparency coef. as ", *line);
		ellipsoid->transperent_coef = mirror;
		*flag = *flag | (1 << 5);
	}
	else
		even_even_more_ellipsoid_fill(line, ellipsoid, line_number, flag);
}

void			more_ellipsoid_fill(char **line,
					t_objects *ellipsoid, int line_number, int *flag)
{
	float	mirror;

	if (begin_with(*line, "mir:"))
	{
		*line = trim_from(*line, 4);
		mirror = str_to_float(*line, 0, line_number);
		if (mirror > 1 || mirror < 0)
			error_caster(line_number, "no such mirror coef. as ", *line);
		ellipsoid->mirror_coef = mirror;
		*flag = *flag | (1 << 3);
	}
	else if (begin_with(*line, "b_p:"))
	{
		*line = trim_from(*line, 4);
		if ((ellipsoid->bling_phong = ft_atoi(*line)) <= 0)
			error_caster(line_number, "no such biling-phong coef. as ", *line);
		*flag = *flag | (1 << 4);
	}
	else
		even_more_ellipsoid_fill(line, ellipsoid, line_number, flag);
}
