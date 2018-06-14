/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:30:52 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/03 15:31:18 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_strl(char const *s, int i, char c)
{
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static int		words(char const *s, char c)
{
	int nb;

	nb = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s == c || *(s + 1) == 0)
		{
			nb++;
			while (*s && (*s == c || *(s + 1) == 0))
				s++;
			s--;
		}
		s++;
	}
	return (nb);
}

static char		*str_create(char const *s, int i, char c)
{
	char	*tmp;
	int		j;

	j = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strl(s, i, c)))))
		return (NULL);
	while (s[i] != c && s[i])
		tmp[j++] = s[i++];
	tmp[j] = 0;
	return (tmp);
}

char			**error_msg(void)
{
	write(1, "ft_strsplit passed pointer is NULL\n", 35);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		nb;
	int		len;

	i = 0;
	nb = 0;
	if (!s)
		return (error_msg());
	len = words(s, c);
	if (!(arr = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!(arr[nb++] = str_create(s, i, c)))
			return (NULL);
		while (s[i] && s[i] != c)
			i++;
	}
	arr[len] = NULL;
	return (arr);
}
