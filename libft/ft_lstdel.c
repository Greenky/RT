/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:26:34 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/07 20:26:44 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*begin;
	t_list	*next;

	if (!alst)
		return ;
	begin = *alst;
	while (begin)
	{
		next = begin->next;
		del(begin->content, begin->content_size);
		free(begin);
		begin = next;
	}
	*alst = NULL;
}
