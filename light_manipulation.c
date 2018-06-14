/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:36:26 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/02 15:36:27 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static void		add_light(t_light **light_list, t_light *light)
{
	t_light *step;

	light->next = NULL;
	step = *light_list;
	if (step)
	{
		while (step->next)
			step = step->next;
		step->next = light;
	}
	else
		*light_list = light;
}

static void		more_of_feelings(char **line, t_light *light, int l_num,
int *flag)
{
	double		intence;

	if (begin_with(*line, "col:"))
	{
		*line = trim_from(*line, 4);
		light->color = parce_color(*line, l_num);
		*flag = *flag | (1 << 1);
	}
	else if (begin_with(*line, "int:"))
	{
		*line = trim_from(*line, 4);
		*flag = *flag | 1;
		intence = str_to_double(*line, 0, l_num);
		if (intence > 1 || intence < 0)
			error_caster(l_num, "no such intence as ", *line);
		light->intence = intence;
	}
	else
		error_caster(l_num, "no such parameter as ", *line);
}

static void		feelings(char **line, t_light *light, int l_num, int *flag)
{
	char *new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (ft_strequ(*line, "point"))
	{
		light->is_dir = 0;
		*flag = (*flag & ~(1 << 3)) | (1 << 4);
	}
	else if (ft_strequ(*line, "direct"))
	{
		light->is_dir = 1;
		*flag = (*flag & ~(1 << 4)) | (1 << 3);
	}
	else if ((begin_with(*line, "dir:") && (*flag & (1 << 3))) ||
	(begin_with(*line, "cen:") && (*flag & (1 << 4))))
	{
		*line = trim_from(*line, 4);
		light->direct = parce_vector(*line, l_num);
		*flag = *flag | (1 << 2);
	}
	else
		more_of_feelings(line, light, l_num, flag);
}

int				light_parce(int fd, int *l_num, void **light_list, int n)
{
	int			flag;
	char		*line;
	int			k;
	t_light		*light;

	flag = 0;
	light = (t_light *)malloc(sizeof(t_light));
	n++;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(*l_num)++;
		feelings(&line, light, *l_num, &flag);
		ft_strdel(&line);
		if (flag == 15 || flag == 23)
			break ;
	}
	if (k < 0)
	{
		free(light);
		perror("RTv1");
		exit(1);
	}
	add_light((t_light **)light_list, light);
	return (0);
}
