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

#include "gfx.h"

int				parce_color(char *line, int l_num)
{
	int			i;
	int			j;
	int			col;
	const char	base[16] = "0123456789ABCDEF";

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
				error_caster(l_num, "wrong color representation ", line);
			col = col * 16 + j;
		}
		return (col);
	}
	error_caster(l_num, "wrong color representation ", line);
	return (0);
}

static double	float_finder(char *line, int *i, int l_num)
{
	double a;

	a = str_to_double(line, *i, l_num);
	while (line[*i] && (line[*i] != ',' || ft_isdigit(line[*i]) ||
	line[*i] == '.'))
		(*i)++;
	while (line[++(*i)] && line[(*i)] < 33)
		;
	return (a);
}

t_vector		parce_vector(char *line, int l_num)
{
	int		i;
	int		flag;
	double	a;
	double	b;
	double	c;

	i = 1;
	flag = 0;
	if (begin_with(line, "("))
	{
		a = float_finder(line, &i, l_num);
		b = float_finder(line, &i, l_num);
		c = str_to_double(line, i, l_num);
		while (line[i])
		{
			if (line[i] == ')')
				return (set_vector(a, b, c));
			i++;
		}
	}
	error_caster(l_num, "wrong vector format ", line);
	return (set_vector(0, 0, 0));
}

void			freesher(t_light **light, t_shape **sh)
{
	t_light *step_li;
	t_shape *step_sh;

	while (*light)
	{
		step_li = (*light)->next;
		free(*light);
		*light = step_li;
	}
	while (*sh)
	{
		step_sh = (*sh)->next;
		free((*sh)->shape);
		free(*sh);
		*sh = step_sh;
	}
}
