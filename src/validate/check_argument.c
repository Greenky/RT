/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 17:02:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/16 14:55:44 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int		check_argument(int fd)
{
	char	*scene_name;

	if (fd == -1)
		ft_putendl("Error file");
	else
	{
		scene_name = is_scene(fd);
		if (scene_name != NULL)
		{
			ft_memdel((void**)&scene_name);
			return (TRUE);
		}
		else
			ft_putendl("Error name of file");
	}
	return (FALSE);
}

char	*is_scene(int fd)
{
	char	*line;

	if (get_next_line(fd, &line) <= 0)
		return (NULL);
	if (!ft_strcmp(line, "scene_1") ||
		!ft_strcmp(line, "scene_2") ||
		!ft_strcmp(line, "scene_3") ||
		!ft_strcmp(line, "scene_4") ||
		!ft_strcmp(line, "scene_5") ||
		!ft_strcmp(line, "scene_6"))
		return (line);
	else
	{
		ft_memdel((void**)&line);
		return (NULL);
	}
}
