/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_peripherals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:49:43 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/01 18:49:44 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

int				begin_with(char *line, char *begin)
{
	int i;

	i = 0;
	if (line && begin)
		while (begin[i])
		{
			if (!line[i])
				return (0);
			if (line[i] != begin[i])
				return (0);
			i++;
		}
	else
		return (0);
	return (1);
}

char			*trim_from(char *line, int i)
{
	char *new_line;

	if (!line)
		exit(1);
	if ((int)ft_strlen(line) >= i)
		while (line[i] && line[i] < 33)
			i++;
	else
		i = 0;
	new_line = ft_strdup(line + i);
	ft_strdel(&line);
	return (new_line);
}

float			str_to_float(char *line, int i, int line_number)
{
	float	num_whole;
	float	negative;

	if (!line)
		return (0);
	negative = 1;
	if (line[i] == '-')
	{
		negative = -1;
		i++;
	}
	if (!ft_isdigit(line[i]))
		error_caster(line_number, "wrong float number representation ", line);
	num_whole = (float)ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i++] == '.')
		num_whole += drob_finder(line, i, line_number);
	return (num_whole * negative);
}

float			drob_finder(char *line, int i, int line_number)
{
	float	num_drob;
	int		len;

	if (!ft_isdigit(line[i]))
		error_caster(line_number, "wrong float number representation ", line);
	len = 0;
	num_drob = (float)ft_atoi(line + i);
	while (ft_isdigit(line[i++]))
		len++;
	num_drob = num_drob / (float)pow(10, len);
	return (num_drob);
}
