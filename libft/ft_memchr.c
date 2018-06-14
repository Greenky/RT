/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:20:37 by vmazurok          #+#    #+#             */
/*   Updated: 2017/10/25 19:20:47 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*src_c;

	src_c = (unsigned char *)src;
	while (n > 0)
	{
		if (*src_c == (unsigned char)c)
			return (src_c);
		src_c++;
		n--;
	}
	return (NULL);
}
