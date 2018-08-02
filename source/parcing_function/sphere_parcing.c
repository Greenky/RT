/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parcing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:41:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/31 21:56:20 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int				sphere_parce(int fd, t_rt *rt_data)
{
	int			ret;
	int			flag;
	char		*line;
	t_objects	*sphere;

	flag = 0;
	sphere = (t_objects *)malloc(sizeof(t_objects));
	sphere->cap[0].dist = INFINITY;
	sphere->cap[1].dist = INFINITY;
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
	sphere->basis.b_z = VEC(1, 0.2, 0);
	add_obj_to_list(rt_data, sphere);
	return (0);
}

void			even_even_more_sphere_fill(char **line,
						t_objects *sphere, int line_number, int *flag)
{
	float	mirror;

	if (begin_with(*line, "texture index:"))
	{
		*line = trim_from(*line, 14);
		if ((sphere->texture_index = ft_atoi(*line)) < -1
			|| sphere->texture_index > 12)
			error_caster(line_number, "no such texture index. as ", *line);
		mirror = 0;
		while ((*line)[(int)mirror] && (*line)[(int)mirror] != ',')
			mirror++;
		*line = trim_from(*line, (int)mirror + 1);
		sphere->texture_repeat = (begin_with(*line, "repeat")
								? ft_atoi((*line) + 7) : 1);
		if (sphere->texture_repeat < 0)
			error_caster(line_number,
						"no such texture repeat number. as ", *line);
		*flag = *flag | (1 << 6);
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

void			even_more_sphere_fill(char **line,
						t_objects *sphere, int line_number, int *flag)
{
	if (begin_with(*line, "b_p:"))
	{
		*line = trim_from(*line, 4);
		if ((sphere->bling_phong = ft_atoi(*line)) <= 0)
			error_caster(line_number, "no such biling-phong coef. as ", *line);
		*flag = *flag | (1 << 5);
	}
	else
		even_even_more_sphere_fill(line, sphere, line_number, flag);
}

void			more_sphere_fill(char **line,
								t_objects *sphere, int line_number, int *flag)
{
	float	mirror;

	sphere->type = SPHERE;
	if (begin_with(*line, "mir:"))
	{
		*line = trim_from(*line, 4);
		mirror = str_to_float(*line, 0, line_number);
		if (mirror > 1 || mirror < 0)
			error_caster(line_number, "no such mirror coef. as ", *line);
		sphere->mirror_coef = mirror;
		*flag = *flag | (1 << 3);
	}
	else if (begin_with(*line, "trancper:"))
	{
		*line = trim_from(*line, 9);
		mirror = str_to_float(*line, 0, line_number);
		if (mirror > 1 || mirror < 0)
			error_caster(line_number, "no such trancparency coef. as ", *line);
		sphere->transperent_coef = mirror;
		*flag = *flag | (1 << 4);
	}
	else
		even_more_sphere_fill(line, sphere, line_number, flag);
}

void			sphere_fill(char **line,
							t_objects *sphere, int line_number, int *flag)
{
	char	*new_line;

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
	else
		more_sphere_fill(line, sphere, line_number, flag);
}
