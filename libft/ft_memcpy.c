/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 18:25:02 by vmazurok          #+#    #+#             */
/*   Updated: 2017/10/25 18:36:34 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_c;
	unsigned char	*dst_c;

	src_c = (unsigned char *)src;
	dst_c = (unsigned char *)dst;
	i = -1;
	while (++i < n)
		dst_c[i] = src_c[i];
	return (dst);
}
