/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 21:56:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/16 15:10:06 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int		check_light(int fd, char **line, t_light *lamp, int lamp_num)
{
	if (lamp_num == 1)
	{
		if (check_existence_word(fd, line, "Light:") == FALSE)
			return (FALSE);
	}
	if (check_existence_word(fd, line, "***") == FALSE)
		return (FALSE);
	if (check_type_light(fd, line, &(lamp->type)) == FALSE)
		return (FALSE);
	if (lamp->type == SPOT)
	{
		if (check_origin(fd, line, &(lamp->origin)) == FALSE)
			return (FALSE);
	}
	if (check_color(fd, line, &(lamp->color)) == FALSE)
		return (FALSE);
	if (check_brightness(fd, line, &(lamp->brightness)) == FALSE)
		return (FALSE);
	return (TRUE);
}

int		check_brightness(int fd, char **line, float *brightness)
{
	char	*s;

	if (get_next_line(fd, line) <= 0)
		return (FALSE);
	if (ft_strncmp(*line, "brightness = ", 13) != 0)
		return (FALSE);
	s = ft_find_after_c(*line, '=');
	*brightness = atoif(s);
	ft_memdel((void**)line);
	if (*brightness < 0.0 || *brightness > 1.0)
		return (FALSE);
	else
		return (TRUE);
}

int		check_type_light(int fd, char **line, int *type)
{
	char	*s;

	if (get_next_line(fd, line) <= 0)
		return (FALSE);
	if (ft_strncmp(*line, "type = ", 7) != 0)
		return (FALSE);
	s = ft_find_after_c(*line, '=');
	if (s == NULL || *s == '\0')
		return (FALSE);
	if (ft_strcmp(s, " AMBIENT") == 0)
		*type = AMBIENT;
	else if (ft_strcmp(s, " SPOT") == 0)
		*type = SPOT;
	else
		return (FALSE);
	ft_memdel((void**)line);
	return (TRUE);
}

int		check_color(int fd, char **line, t_channel *color)
{
	char	*s;

	if (get_next_line(fd, line) <= 0)
		return (FALSE);
	if (ft_strncmp(*line, "color = ", 8) != 0)
		return (FALSE);
	s = ft_find_after_c(*line, '{');
	if (s == NULL || *s == '\0')
		return (FALSE);
	color->red = ft_atoi(s);
	s = ft_find_after_c(s, ' ');
	if (s == NULL || *s == '\0')
		return (FALSE);
	color->green = ft_atoi(s);
	s = ft_find_after_c(s, ' ');
	if (s == NULL || *s == '\0')
		return (FALSE);
	color->blue = ft_atoi(s);
	if (color->red < 0 || color->red > 255 || color->green < 0 ||
		color->green > 255 || color->blue < 0 || color->blue > 255)
		return (FALSE);
	ft_memdel((void**)line);
	return (TRUE);
}
