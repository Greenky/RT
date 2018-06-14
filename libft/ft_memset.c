/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:27:00 by vmazurok          #+#    #+#             */
/*   Updated: 2017/10/25 17:27:03 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *arr, int val, size_t num)
{
	unsigned char	*temp;
	size_t			i;

	if (num == 0)
		return (arr);
	temp = (unsigned char *)arr;
	i = 0;
	while (num--)
	{
		temp[i] = (unsigned char)val;
		if (num != 0)
			i++;
	}
	return (arr);
}
