/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:52:03 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/01 17:54:15 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*fresh;

	i = 0;
	if (!(fresh = (char *)malloc(size + 1)))
	{
		write(1, "Can't malloc in ft_strnew\n", 26);
		return (NULL);
	}
	i = 0;
	while (i < size + 1)
	{
		fresh[i] = 0;
		i++;
	}
	return (fresh);
}
