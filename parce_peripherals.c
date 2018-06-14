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

#include "gfx.h"

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

static double	drob_finder(char *line, int i, int l_num)
{
	double	num_drob;
	int		len;

	if (!ft_isdigit(line[i]))
		error_caster(l_num, "wrong float number representation ", line);
	len = 0;
	num_drob = (double)ft_atoi(line + i);
	while (ft_isdigit(line[i++]))
		len++;
	num_drob = num_drob / pow(10, len);
	return (num_drob);
}

double			str_to_double(char *line, int i, int l_num)
{
	double	num_whole;
	double	negative;

	if (!line)
		return (0);
	negative = 1;
	if (line[i] == '-')
	{
		negative = -1;
		i++;
	}
	if (!ft_isdigit(line[i]))
		error_caster(l_num, "wrong float number representation ", line);
	num_whole = (double)ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i++] == '.')
		num_whole += drob_finder(line, i, l_num);
	return (num_whole * negative);
}

void			error_caster(int line_number, char *s1, char *s2)
{
	char	*line;

	ft_putstr("error in line ");
	ft_putnbr(line_number);
	ft_putstr("\n");
	ft_putstr(s1);
	ft_putstr("\"");
	ft_putstr(s2);
	ft_putendl("\"");
	line = ft_strjoin(s1, s2);
	ft_strdel(&s2);
	s2 = ft_strjoin("say \"", line);
	ft_strdel(&line);
	line = ft_strjoin(s2, "\"");
	system(line);
	ft_strdel(&s2);
	ft_strdel(&line);
	exit(1);
}
