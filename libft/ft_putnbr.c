/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 21:29:54 by vmazurok          #+#    #+#             */
/*   Updated: 2017/09/25 21:34:45 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putik(char c)
{
	write(1, &c, 1);
}

void		ft_putnbr(int nb)
{
	int s[10];
	int	i;
	int num;

	i = 0;
	num = nb;
	if (num == -2147483648)
		nb++;
	if (nb < 0)
	{
		ft_putik('-');
		nb = nb * (-1);
	}
	if (nb == 0)
		ft_putik('0');
	while (nb != 0)
	{
		s[i] = nb % 10;
		nb = nb / 10;
		i++;
	}
	if (num == -2147483648)
		s[0] = 8;
	while (i-- > 0)
		ft_putik(s[i] + '0');
}
