/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmpnoreg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:07:37 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/09 20:14:09 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cmpnoreg(const char *s1, const char *s2)
{
	int		i;
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = -1;
	while (str1[++i])
		str1[i] = ft_tolower(str1[i]);
	i = -1;
	while (str2[++i])
		str2[i] = ft_tolower(str2[i]);
	return (ft_strcmp(str1, str2));
}
