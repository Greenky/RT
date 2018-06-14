/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 20:34:12 by vmazurok          #+#    #+#             */
/*   Updated: 2017/09/25 20:34:19 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	chekni_pleas(char *str, int n, int sign)
{
	unsigned long long number;

	number = 0;
	while (str[n] > 47 && str[n] < 58)
	{
		number = number * 10 + (str[n] - 48);
		if (number > 9223372036854775807 && sign == 1)
			return (-1);
		if (number > 9223372036854775807 && sign == -1)
			return (0);
		n++;
	}
	return (sign * (int)number);
}

int			ft_atoi(const char *str)
{
	int	n;
	int	num;

	n = 0;
	num = 0;
	while (str[n] != '\0')
	{
		if ((str[n] >= 9 && str[n] <= 13) || str[n] == 32)
			n++;
		else
			break ;
	}
	if (str[n] == '-')
		num = chekni_pleas((char *)str, n + 1, -1);
	else if (str[n] == '+')
		num = chekni_pleas((char *)str, n + 1, 1);
	else
		num = chekni_pleas((char *)str, n, 1);
	return (num);
}
