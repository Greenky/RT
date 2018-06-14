/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:57:00 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/01 19:05:19 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*error_msg(void)
{
	write(1, "f or s in ft_strmap is NULL\n", 29);
	return (NULL);
}

char		*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		nb;
	char	*new;

	if (s == NULL || f == NULL)
		return (error_msg());
	i = 0;
	nb = 0;
	while (s[nb])
		nb++;
	if (!(new = (char *)malloc(sizeof(char) * (nb + 1))))
		return (NULL);
	nb = 0;
	while (s[i])
	{
		if (f(s[i]))
		{
			new[nb] = f(s[i]);
			nb++;
		}
		i++;
	}
	new[nb] = 0;
	return (new);
}
