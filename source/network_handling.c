/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:32:34 by vmazurok          #+#    #+#             */
/*   Updated: 2018/07/31 18:55:30 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

static void		connect_to_client(t_rt *rt_data, int client,
				struct sockaddr_in server_addr, char *file)
{
	socklen_t	size;

	size = sizeof(server_addr);
	listen(client, 1);
	rt_data->server_fd = accept(client, (struct sockaddr *)&server_addr, &size);
	if (rt_data->server_fd < 0)
	{
		write(2, "=> Error on accepting...", 24);
		return ;
	}
	send_data(rt_data->server_fd, file, ft_strlen(file));
}

void			init_server(t_rt *rt_data, char *file)
{
	int					client;
	struct sockaddr_in	server_addr;

	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client < 0)
	{
		write(2, "\nError establishing socket...", 29);
		exit(1);
	}
	write(1, "=> Socket server has been created...\n", 37);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(5000);
	if ((bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0)
	{
		write(2, "=> Error binding connection...\n", 31);
		return ;
	}
	write(1, "=> Looking for clients...\n", 26);
	connect_to_client(rt_data, client, server_addr, file);
}

void			*receive_data(int fd, void *dest, size_t size)
{
	dest = ft_memalloc(size);
	recv(fd, dest, size, 0);
	return (dest);
}

void			send_data(int fd, void *src, size_t size)
{
	unsigned char *buffer;

	buffer = (unsigned char *)ft_memalloc(size);
	ft_memcpy(buffer, src, size);
	send(fd, buffer, size, 0);
	free(buffer);
}
