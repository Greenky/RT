/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parcing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 19:50:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/09 19:50:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int			light_parce(int fd, t_rt *rt_data)
{
	int		flag;
	char	*line;
	int		k;
	t_light	*light;

	flag = 0;
	light = (t_light *)malloc(sizeof(t_light));
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		feelings(&line, light, rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == DIRECT_LIGHT_IS_PARSED
			|| flag == POINT_LIGHT_IS_PARSED || flag == AMBIENT_LIGHT_IS_PARSED)
			break ;
	}
	if (k < 0 || (flag != DIRECT_LIGHT_IS_PARSED
		&& flag != POINT_LIGHT_IS_PARSED && flag != AMBIENT_LIGHT_IS_PARSED))
	{
		free(light);
		perror("RT");
		exit(1);
	}
	add_light(rt_data, light);
	return (0);
}

void		feelings(char **line, t_light *light, int line_number, int *flag)
{
	char *new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (ft_strequ(*line, "ambient"))
	{
		light->type = AMBIENT;
		*flag = *flag | (1 << 5);
	}
	else if (ft_strequ(*line, "point"))
	{
		light->type = POINT;
		*flag = (*flag & ~(1 << 3)) | (1 << 4);
	}
	else
		more_of_feelings(line, light, line_number, flag);
}

static void	even_more_of_feelings(char **line, t_light *light, int line_number,
									int *flag)
{
	float	intensity;

	if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		light->color = parce_color(*line, line_number);
		*flag = *flag | (1 << 1);
	}
	else if (begin_with(*line, "int:"))
	{
		*line = trim_from(*line, 4);
		*flag = *flag | 1;
		intensity = str_to_float(*line, 0, line_number);
		if (intensity > 1 || intensity < 0)
			error_caster(line_number, "no such intensity as ", *line);
		light->intensity = intensity;
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

void		more_of_feelings(char **line, t_light *light, int line_number,
									int *flag)
{
	if (ft_strequ(*line, "direct"))
	{
		light->type = DIRECT;
		*flag = (*flag & ~(1 << 4)) | (1 << 3);
	}
	else if (begin_with(*line, "dir:") && (*flag & (1 << 3)))
	{
		*line = trim_from(*line, 4);
		light->direct = parce_vector(*line, line_number);
		*flag = *flag | (1 << 2);
	}
	else if (begin_with(*line, "cen:") && (*flag & (1 << 4)))
	{
		*line = trim_from(*line, 4);
		light->origin = parce_vector(*line, line_number);
		*flag = *flag | (1 << 2);
	}
	else
		even_more_of_feelings(line, light, line_number, flag);
}
