/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:21:03 by vmazurok          #+#    #+#             */
/*   Updated: 2017/10/26 19:24:59 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_trigon(float num, char c)
{
	float	n;
	float	ans;

	n = -1;
	ans = 0;
	while (num > 2 * PI)
		num -= (2 * PI);
	while (num < 0)
		num += (2 * PI);
	if (c == 's' || c == 'S')
		while (++n < 10)
			ans = ans + (ft_pow(-1, n) * ft_pow(num, 2 * n + 1)) /
		(float)ft_factorial(2 * n + 1);
	else if (c == 'c' || c == 'C')
		while (++n < 10)
			ans = ans + (ft_pow(-1, n) * ft_pow(num, 2 * n)) /
		(float)ft_factorial(2 * n);
	return (ans);
}
