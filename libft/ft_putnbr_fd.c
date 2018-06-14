/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:21:55 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/07 10:22:19 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putik(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putnbr_fd(int nb, int fd)
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
		ft_putik('-', fd);
		nb = nb * (-1);
	}
	if (nb == 0)
		ft_putik('0', fd);
	while (nb != 0)
	{
		s[i] = nb % 10;
		nb = nb / 10;
		i++;
	}
	if (num == -2147483648)
		s[0] = 8;
	while (i-- > 0)
		ft_putik(s[i] + '0', fd);
}
