/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:37:39 by vmazurok          #+#    #+#             */
/*   Updated: 2017/10/25 19:37:49 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t l1;
	size_t l2;

	l1 = 0;
	if (to_find[0] == 0)
		return ((char *)str);
	while (str[l1] != '\0' && l1 < len - ft_strlen((char *)to_find) + 1)
	{
		if (ft_strlen((char *)to_find) > len)
			return (NULL);
		l2 = 0;
		while (str[l1] == to_find[l2])
		{
			if (to_find[l2 + 1] == '\0')
			{
				return (&(*(char *)(str + l1 - l2)));
			}
			l1++;
			l2++;
		}
		l1 = l1 - l2;
		l1++;
	}
	return (0);
}
