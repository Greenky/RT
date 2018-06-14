/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:55:14 by vmazurok          #+#    #+#             */
/*   Updated: 2017/10/25 17:59:41 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_bzero(void *arr, size_t num)
{
	unsigned char	*temp;
	size_t			i;

	if (num == 0)
		return (arr);
	temp = (unsigned char *)arr;
	i = 0;
	while (num--)
	{
		temp[i] = 0;
		if (num != 0)
			i++;
	}
	return (arr);
}
