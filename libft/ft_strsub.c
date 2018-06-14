/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 21:33:28 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/01 21:44:56 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	n;
	size_t	i;

	if (!s)
	{
		write(1, "ft_strsub parametr is NULL\n", 27);
		return (NULL);
	}
	i = 0;
	n = (size_t)start;
	if (!(str = (char *)malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		str[i] = s[n];
		n++;
		i++;
	}
	str[i] = 0;
	return (str);
}
