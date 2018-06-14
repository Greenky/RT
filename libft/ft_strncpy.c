/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 22:13:37 by vmazurok          #+#    #+#             */
/*   Updated: 2017/09/25 22:47:11 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t l1;

	l1 = 0;
	while (src[l1] != '\0' && l1 < len)
	{
		dest[l1] = src[l1];
		l1++;
	}
	while (l1 < len)
	{
		dest[l1] = '\0';
		l1++;
	}
	return (dest);
}
