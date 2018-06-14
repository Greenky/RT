/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:47:15 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/01 18:53:41 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	if (s == NULL || f == NULL)
	{
		write(1, "f or s in ft_striter is NULL\n", 29);
		return ;
	}
	while (*s)
	{
		f(&(*s));
		s++;
	}
}
