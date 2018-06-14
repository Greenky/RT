/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 19:39:03 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/03 19:39:06 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static int	lencer(int num)
{
	int len;

	len = 0;
	while (num > 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

static char	*zero(void)
{
	char *arr;

	if (!(arr = (char *)malloc(sizeof(char) * 2)))
		return (NULL);
	arr[0] = '0';
	arr[1] = 0;
	return (arr);
}

static	int	chaeacker(int *n)
{
	if (*n == -2147483648)
	{
		*n = *n + 1;
		*n = *n * (-1);
		return (1);
	}
	if (*n < 0)
	{
		*n = *n * (-1);
		return (0);
	}
	return (0);
}

static char	*str_make(int n, int flag)
{
	char	*arr;
	int		len;
	int		cheack;
	int		buf;

	cheack = chaeacker(&n);
	len = lencer(n);
	buf = len;
	if (!(arr = (char *)malloc(sizeof(char) * (len + flag + 1))))
		return (NULL);
	arr[len + flag] = '\0';
	while (--len >= 0)
	{
		arr[len + flag] = n % 10 + '0';
		n = n / 10;
	}
	if (flag)
		arr[0] = '-';
	if (cheack)
		arr[buf] = 8 + '0';
	return (arr);
}

char		*ft_itoa(int n)
{
	char		*arr;
	int			flag;
	int			len;

	flag = 0;
	len = 0;
	if (n == 0)
		return (zero());
	if (n < 0)
		flag = 1;
	arr = str_make(n, flag);
	return (arr);
}
