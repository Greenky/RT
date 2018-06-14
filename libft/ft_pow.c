/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:36:34 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/09 22:36:35 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_pow(float n, int pow)
{
	float val;

	val = 1;
	if (n == 0 && pow == 0)
	{
		write(1, "______Rly, 0^0?______\n", 22);
		return (-1);
	}
	if (pow < 0)
	{
		write(1, "______No minus pows, sore______\n", 32);
		return (-1);
	}
	if (pow == 0)
		return (1);
	while (pow--)
		val *= n;
	return (val);
}
