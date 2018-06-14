/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 15:14:30 by vmazurok          #+#    #+#             */
/*   Updated: 2017/12/14 15:15:15 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		re_malloc(char **line, int n, char *arr, int len)
{
	int		c;
	char	*buff;

	c = 0;
	if (*line)
	{
		c = (int)ft_strlen(*line);
		buff = (char *)ft_memalloc(sizeof(char) * (n + c + 1));
		buff = ft_strncpy(buff, *line, c);
		free(*line);
		*line = buff;
	}
	else
		*line = (char *)ft_memalloc(sizeof(char) * (n + 1));
	if (len != -1)
		ft_strncpy((*line) + c, arr, len);
	else
		ft_strcpy((*line) + c, arr);
	return (1);
}

int		signaturka(char **line, char **tail)
{
	int	i;
	int len;

	i = 0;
	if (!(*tail)[i])
	{
		ft_memdel((void **)tail);
		return (0);
	}
	while ((*tail)[i] && (*tail)[i] != '\n')
		i++;
	re_malloc(line, i, *tail, i);
	len = (int)ft_strlen(*tail) - i;
	if ((*tail)[i] && ft_memmove(*tail, (*tail) + i + 1, len))
	{
		i = -1;
		while ((*tail)[(++i) + len])
			(*tail)[i + len] = 0;
		return (1);
	}
	else
	{
		ft_memdel((void **)tail);
		return (0);
	}
}

t_file	*add_elem(t_file *lst, const int fd)
{
	t_file	*buff;
	t_file	*pepe;

	buff = (t_file *)ft_memalloc(sizeof(t_file));
	buff->fd = fd;
	buff->tail = NULL;
	if (!lst)
		buff->next = buff;
	else
	{
		pepe = lst->next;
		lst->next = buff;
		buff->next = pepe;
	}
	return (buff);
}

int		reader(t_file *lst, char **line, char *arr)
{
	int c;
	int i;

	c = 0;
	i = 0;
	if ((lst->tail) && signaturka(&(*line), &(lst->tail)))
		return (1);
	while (!lst->tail && (c = read(lst->fd, arr, BUFF_SIZE)) > 0)
	{
		i = 0;
		while (arr[i] && arr[i] != '\n')
			i++;
		re_malloc(&(*line), i, arr, i);
		if (arr[i] == '\n' &&
		re_malloc(&(lst->tail), BUFF_SIZE - i, arr + i + 1, -1))
			break ;
		ft_bzero(arr, BUFF_SIZE + 1);
	}
	return (c);
}

int		get_next_line(const int fd, char **line)
{
	char			*arr;
	int				c;
	static t_file	*lst;

	if (!line)
		return (-1);
	*line = NULL;
	arr = (char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!lst)
		lst = add_elem(lst, fd);
	else
	{
		c = lst->fd;
		while (lst->fd != fd && lst->next->fd != c)
			lst = lst->next;
		if (lst->fd != fd)
			lst = add_elem(lst, fd);
	}
	c = reader(lst, line, arr);
	free(arr);
	if (c < 0)
		return (-1);
	return ((c == 0 && !*line) ? 0 : 1);
}
