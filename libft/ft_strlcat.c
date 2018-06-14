/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 20:02:29 by vmazurok          #+#    #+#             */
/*   Updated: 2017/09/26 20:04:58 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	lencer(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	char		*dnew;
	char		*snew;
	size_t		nnew;
	size_t		dlen;

	dnew = dest;
	snew = (char *)src;
	nnew = size;
	while (nnew-- != 0 && *dnew != '\0')
		dnew++;
	dlen = dnew - dest;
	nnew = size - dlen;
	if (nnew == 0)
		return (dlen + lencer(snew));
	while (*snew != '\0')
	{
		if (nnew != 1)
		{
			*dnew++ = *snew;
			nnew--;
		}
		snew++;
	}
	*dnew = '\0';
	return (dlen + (snew - (char *)src));
}
