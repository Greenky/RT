/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:25:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/07 12:25:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

int		find_fd(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit(ERROR, NULL);
	if (read(fd, NULL, 0) == -1)
		error_exit(ERROR, NULL);
	return (fd);
}
