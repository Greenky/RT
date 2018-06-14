/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 11:05:59 by vmazurok          #+#    #+#             */
/*   Updated: 2017/10/26 11:06:23 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	i;
	char	*buf;
	char	*s1;

	s1 = (char *)s;
	buf = NULL;
	i = (char)c;
	while (*s1)
	{
		if (*s1 == i)
			buf = s1;
		else if (*(s1 + 1) == i)
			buf = s1 + 1;
		s1++;
	}
	return (buf);
}
