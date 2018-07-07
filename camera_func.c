/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 20:08:17 by vmazurok          #+#    #+#             */
/*   Updated: 2018/05/23 20:08:19 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_data.h"

static void	camera_data_fill(char **line, t_camera *camera, int line_number, int *flag)
{
	char *buffer_line;

	buffer_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = buffer_line;
	if (begin_with(*line, "dir:"))
	{
		
		*line = trim_from(*line, 4);
		(*camera).direct = v_to_len(parce_vector(*line, line_number), 1, 0);
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		(*camera).origin = parce_vector(*line, line_number);
		*flag = *flag | 2;
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}

int			cam_parce(int fd, t_rt *rt_data, int id)
{
	int			k;
	int			flag;
	char		*line;

	flag = 0;
	id++; // usless line for Wall Wextra Werror ))
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		camera_data_fill(&line, &(rt_data->camera), rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == 3)
			break ;
	}
	if (k < 0)
	{
		perror("RT");
		exit(1);
	}
	rt_data->camera.is_set = 1;
	return (0);
}
