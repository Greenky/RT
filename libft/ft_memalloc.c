/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 09:48:01 by vmazurok          #+#    #+#             */
/*   Updated: 2017/10/31 09:48:05 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void			*str;
	unsigned char	*temp;
	size_t			i;

	if (!(str = malloc(size)))
		return (NULL);
	temp = (unsigned char *)str;
	i = 0;
	while (size--)
	{
		temp[i] = 0;
		if (size != 0)
			i++;
	}
	return (str);
}
