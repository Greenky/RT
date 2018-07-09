/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:43:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/16 15:46:35 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int		read_file(t_scene_data *scene, int fd)
{
	char	*line;

	line = NULL;
	if (!check_camera(fd, &line, scene))
	{
		ft_memdel((void**)&line);
		return (FALSE);
	}
	init_figures(fd, &line, &(scene->figures));
	if (scene->figures == NULL)
		return (FALSE);
	init_lights(fd, line, &(scene->lights));
	if (scene->lights == NULL)
		return (FALSE);
	return (TRUE);
}

void	init_figures(int fd, char **line, t_list **figures)
{
	t_figure	*fig;
	t_list		*node;
	t_list		*tmp;
	int			fig_num;

	fig_num = 1;
	tmp = NULL;
	while (TRUE)
	{
		(*figures) = tmp;
		node = malloc(sizeof(t_list));
		fig = malloc(sizeof(t_figure));
		node->content = fig;
		node->next = tmp;
		if (check_figure(fd, line, fig, fig_num) == FALSE)
		{
			ft_memdel((void**)line);
			ft_memdel((void**)&fig);
			ft_memdel((void**)&node);
			break ;
		}
		fig_num++;
		tmp = node;
	}
}

void	init_lights(int fd, char *line, t_list **lights)
{
	t_light		*lamp;
	t_list		*node;
	t_list		*tmp;
	int			lamp_num;

	lamp_num = 1;
	tmp = NULL;
	while (TRUE)
	{
		(*lights) = tmp;
		node = malloc(sizeof(t_list));
		lamp = malloc(sizeof(t_figure));
		node->content = lamp;
		node->next = tmp;
		if (check_light(fd, &line, lamp, lamp_num) == FALSE)
		{
			ft_memdel((void**)&line);
			ft_memdel((void**)&lamp);
			ft_memdel((void**)&node);
			break ;
		}
		ft_memdel((void**)&line);
		lamp_num++;
		tmp = node;
	}
}
