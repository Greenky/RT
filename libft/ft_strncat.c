/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 20:02:29 by vmazurok          #+#    #+#             */
/*   Updated: 2017/09/26 20:04:58 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	size_t l1;
	size_t l2;
	size_t i;

	l1 = 0;
	l2 = 0;
	while (dest[l1] != 0)
		l1++;
	while (src[l2] != 0)
		l2++;
	i = 0;
	while (i < l2 && i < nb)
	{
		dest[l1 + i] = src[i];
		i++;
	}
	dest[l1 + i] = 0;
	return (dest);
}
