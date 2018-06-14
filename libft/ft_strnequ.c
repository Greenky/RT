/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 21:10:00 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/01 21:14:14 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int i;

	i = 0;
	n++;
	if (!(s1) || !(s2))
		return (0);
	if (s1[0] == 0 && s2[0] == 0)
		return (1);
	while ((s1[i] || s2[i]) && n != 1)
	{
		if (s1[i] != s2[i])
			return (0);
		else if (s1[i + 1] == 0 && s2[i + 1] == 0)
			return (1);
		i++;
		n--;
	}
	if (n == 1)
		return (1);
	else
		return (0);
}
