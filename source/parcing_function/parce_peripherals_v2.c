/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_peripherals_v2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:57:19 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/01 18:57:20 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

t_channel		int_to_channels(int col)
{
	t_channel	channels;

	channels.blue = col & 255;
	channels.green = col >> 8 & 255;
	channels.red = col >> 16 & 255;
	return (channels);
}

t_channel		parce_color(char *line, int line_number)
{
	int			i;
	int			j;
	int			col;
	const char	base[17] = "0123456789ABCDEF";

	i = 1;
	col = 0;
	if (begin_with(line, "0x"))
	{
		while (line[++i])
		{
			j = 0;
			while (base[j] && base[j] != ft_toupper(line[i]))
				j++;
			if (!base[j])
				error_caster(line_number, "wrong color representation ", line);
			col = col * 16 + j;
		}
		return (int_to_channels(col));
	}
	error_caster(line_number, "wrong color representation ", line);
	return ((t_channel){0, 0, 0});
}

cl_float3		parce_vector(char *line, int line_number)
{
	int		i;
	float	a;
	float	b;
	float	c;

	i = 1;
	if (begin_with(line, "("))
	{
		a = float_finder(line, &i, line_number);
		b = float_finder(line, &i, line_number);
		c = str_to_float(line, i, line_number);
		while (line[i])
		{
			if (line[i] == ')')
				return (VEC(a, b, c));
			i++;
		}
	}
	error_caster(line_number, "wrong vector format ", line);
	return (VEC(0, 0, 0));
}

float			float_finder(char *line, int *i, int line_number)
{
	float	a;

	a = str_to_float(line, *i, line_number);
	while (line[*i] && (line[*i] != ',' || ft_isdigit(line[*i]) ||
						line[*i] == '.'))
		(*i)++;
	while (line[++(*i)] && line[(*i)] < 33)
		;
	return (a);
}
