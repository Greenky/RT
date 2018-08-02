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
	cone->cap[0].dist = INFINITY;
	cone->cap[1].dist = INFINITY;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		cone_data_fill(&line, cone, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == CONE_IS_PARSED)
			break ;
	}
	if (k < 0 || flag != CONE_IS_PARSED)
		error_exit(ERROR, NULL);
	add_obj_to_list(rt_data, cone);
	return (0);
}

void			cone_data_fill(char **line, t_objects *cone,
									int line_number, int *flag)
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

static void		more_cone_data_fill3(char **line, t_objects *cone,
										int line_number, int *flag)
{
	float	mirror;

	if (begin_with(*line, "texture index:"))
	{
		*line = trim_from(*line, 14);
		if ((cone->texture_index = ft_atoi(*line)) < -1
			|| cone->texture_index > 12)
			error_caster(line_number, "no such texture index. as ", *line);
		mirror = 0;
		while ((*line)[(int)mirror] && (*line)[(int)mirror] != ',')
			mirror++;
		*line = trim_from(*line, (int)mirror + 1);
		cone->texture_repeat = (begin_with(*line, "repeat")
								? ft_atoi((*line) + 7) : 1);
		if (cone->texture_repeat < 0)
			error_caster(line_number,
						"no such texture repeat number. as ", *line);
		*flag = *flag | (1 << 7);
	}
	else if (begin_with(*line, "limited"))
		parce_limited(line, cone, line_number, flag);
	else
		error_caster(line_number, "no such parameter as ", *line);
}

static void		more_cone_data_fill2(char **line, t_objects *cone,
										int line_number, int *flag)
{
	float	mirror;

	if (begin_with(*line, "mir:"))
	{
		*line = trim_from(*line, 4);
		mirror = str_to_float(*line, 0, line_number);
		if (mirror > 1 || mirror < 0)
			error_caster(line_number, "no such mirror coef. as ", *line);
		cone->mirror_coef = mirror;
		*flag = *flag | (1 << 5);
	}
	else if (begin_with(*line, "trancper:"))
	{
		*line = trim_from(*line, 9);
		if ((mirror = str_to_float(*line, 0, line_number)) > 1 || mirror < 0)
			error_caster(line_number, "no such trancparency coef. as ", *line);
		cone->transperent_coef = mirror;
		*flag = *flag | (1 << 6);
	}
	else
		more_cone_data_fill3(line, cone, line_number, flag);
}

void			more_cone_data_fill(char **line, t_objects *cone,
									int line_number, int *flag)
{
	if (begin_with(*line, "ang:"))
	{
		*line = trim_from(*line, 4);
		cone->angle_coef = fminf(1, fmaxf(0.05,
			tanf(ANGLE_IN_DEGREES(str_to_float(*line, 0, line_number)))));
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
		more_cone_data_fill2(line, cone, line_number, flag);
}
