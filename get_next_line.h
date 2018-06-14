/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:36:36 by vmazurok          #+#    #+#             */
/*   Updated: 2017/12/07 18:36:38 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 50
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_file
{
	int				fd;
	char			*tail;
	struct s_file	*next;
}				t_file;

int				get_next_line(const int fd, char **line);

#endif
