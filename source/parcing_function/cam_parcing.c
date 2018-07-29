/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parcing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:58:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/07 12:58:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int		cam_parce(int fd, t_rt *rt_data)
{
	int			ret;
	int			flag;
	char		*line;

	flag = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		(rt_data->line_number)++;
		camera_data_fill(&line, &(rt_data->cl_data.camera),
						rt_data->line_number, &flag);
		ft_strdel(&line);
		if (flag == CAMERA_IS_PARSED)
			break ;
	}
	if (ret < 0 || flag != CAMERA_IS_PARSED)
		error_exit(ERROR, NULL);
	rt_data->cl_data.camera.is_set = 1;
	create_coord_system(&(rt_data->cl_data.camera.basis),
					&(rt_data->cl_data.camera.initial_basis),
					&(rt_data->cl_data.camera.angle_rot));
	return (0);
}

void	camera_data_fill(char **line,
						t_camera *camera, int line_number, int *flag)
{
	char	*buffer_line;

	buffer_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = buffer_line;
	if (begin_with(*line, "dir:"))
	{
		*line = trim_from(*line, 4);
		camera->basis.b_z = normalize_vector(parce_vector(*line, line_number));
		*flag = *flag | 1;
	}
	else if (begin_with(*line, "cen:"))
	{
		*line = trim_from(*line, 4);
		camera->origin = parce_vector(*line, line_number);
		*flag = *flag | 2;
	}
	else
		error_caster(line_number, "no such parameter as ", *line);
}
