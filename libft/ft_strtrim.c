/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:19:39 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/03 18:20:08 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static int		lencer(const char *s)
{
	int i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (s[i])
	{
		i++;
		len++;
	}
	while (s[--i] == ' ' || s[i] == '\n' || s[i] == '\t')
		len--;
	return (len);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		len;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if ((len = lencer(s)) <= 0)
	{
		if (!(str = (char *)malloc(sizeof(char) * (1))))
			return (NULL);
		*str = '\0';
		return (str);
	}
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (j < len)
		str[j++] = s[i++];
	str[j] = 0;
	return (str);
}
