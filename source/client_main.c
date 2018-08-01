/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 18:00:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/31 18:57:45 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

int		run_rt_client(int client, struct sockaddr_in server_addr)
{
	char	*str_ka;
	t_rt	rt_data;

	if (connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr))
	== 0)
		ft_putendl("=> Connection to the server port number: 5000");
	else
	{
		write(2, "Connection faled\n", 17);
		exit(1);
	}
	str_ka = NULL;
	str_ka = (char *)receive_data(client, str_ka, 100);
	rt_data.server_fd = client;
	rt_data.is_client = 1;
	file_parcing(str_ka, &rt_data);
	init_gui_bmps(&rt_data);
	init_foot_gui_bmps(&rt_data);
	rt_data.aliasing = 0;
	rt_data.filter = NOFILTER;
	rt_data.gui.filter_gui = 0;
	init_bar_positions(&rt_data);
	run_rt(&rt_data);
	return (0);
}

int		main(int ac, char **av)
{
	int					client;
	struct sockaddr_in	server_addr;
	struct hostent		*p_host_info;

	client = socket(AF_INET, SOCK_STREAM, 0);
	if (ac != 2)
	{
		write(2, "No(\n", 4);
		exit(1);
	}
	if (client < 0)
	{
		write(2, "Error establishing socket...\n", 29);
		exit(1);
	}
	write(1, "Socket client has been created...\n", 34);
	p_host_info = gethostbyname(av[1]);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000);
	ft_memcpy(&server_addr.sin_addr, p_host_info->h_addr,
	(size_t)p_host_info->h_length);
	return (run_rt_client(client, server_addr));
}
