/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:15:43 by vmazurok          #+#    #+#             */
/*   Updated: 2017/10/25 19:17:58 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_c;
	unsigned char	*dst_c;

	src_c = (unsigned char *)src;
	dst_c = (unsigned char *)dst;
	i = 0;
	if (n == 0)
		return (dst);
	if (dst < src)
	{
		while (i < n)
		{
			dst_c[i] = src_c[i];
			i++;
		}
	}
	else
	{
		while (--n > 0)
			dst_c[n] = src_c[n];
		*dst_c = *src_c;
	}
	return (dst);
}
