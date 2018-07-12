/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 11:28:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 14:12:10 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

float	atoif(char *str)
{
	int		integer;
	float	fractional;

	integer = ft_atoi(str);
	str = ft_find_after_c(str, '.');
	if (str == NULL || *str == '\0')
		return ((float)integer);
	fractional = (float)ft_atoi(str);
	while (fractional >= 1)
		fractional /= 10;
	fractional += integer;
	return (fractional);
}
