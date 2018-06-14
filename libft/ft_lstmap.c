/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:26:45 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/08 14:26:46 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *tmp;
	t_list *new_next;

	tmp = NULL;
	if (!f)
		return (NULL);
	while (!(tmp = f(lst)) && lst)
		lst = lst->next;
	if (!tmp || !(new_next = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	new = new_next;
	if (lst)
		lst = lst->next;
	while (lst)
	{
		if ((tmp = f(lst)))
		{
			if (!(new_next->next = ft_lstnew(tmp->content, tmp->content_size)))
				return (NULL);
			new_next = new_next->next;
		}
		lst = lst->next;
	}
	return (new);
}
