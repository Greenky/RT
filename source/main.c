/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 20:08:17 by vmazurok          #+#    #+#             */
/*   Updated: 2018/05/23 20:08:19 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(2);
}

void	cl_init(t_rt *rt)
{
	int		fd;
	char	*src;
	size_t	src_size;

	fd = open("kernel.cl", O_RDONLY);
	if (fd <= 0)
		ft_error("Failed to load kernel.");
	src = (char *)malloc(MAX_SRC_SIZE);
	src_size = (size_t)read(fd, src, MAX_SRC_SIZE);
	close(fd);
	rt->cl.err = clGetPlatformIDs(1, &rt->cl.platform_id,
								  &rt->cl.platforms_num);
	ft_putendl("clGetPlatformIDs done.");
	rt->cl.err |= clGetDeviceIDs(rt->cl.platform_id, CL_DEVICE_TYPE_CPU,
								1, &rt->cl.device_id, &rt->cl.devices_num);
	ft_putendl("clGetDeviceIDs done.");
	rt->cl.context = clCreateContext(NULL, 1, &rt->cl.device_id, NULL,
									 NULL, &rt->cl.err);
	ft_putendl("clCreateContext done.");
	rt->cl.queue = clCreateCommandQueue(rt->cl.context, rt->cl.device_id,
										0, &rt->cl.err);
	ft_putendl("clCreateCommandQueue done.");
	rt->cl.program = clCreateProgramWithSource(rt->cl.context, 1,
											   (const char **)&src, (const size_t *)&src_size, &rt->cl.err);
	ft_putendl("clCreateProgramWithSource done.");
	rt->cl.err |= clBuildProgram(rt->cl.program, 1, &rt->cl.device_id, NULL,
										 NULL, NULL);
	ft_putendl("clBuildProgram done.");
	if (rt->cl.err != CL_SUCCESS) {
		// Determine the size of the log
		size_t log_size;
		clGetProgramBuildInfo(rt->cl.program, rt->cl.device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

		// Allocate memory for the log
		char *log = (char *) malloc(log_size);

		// Get the log
		clGetProgramBuildInfo(rt->cl.program, rt->cl.device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

		// Print the log
		printf("%s\n", log);
	}
	rt->cl.kernel = clCreateKernel(rt->cl.program, "renderer", &rt->cl.err);
	ft_putendl("clCreateKernel done.");
	free(src);
}

int			main(int argc, char **argv)
{
	t_rt	rt_data;
//	if (argc != 2)
//		error_exit(NUM_OF_ARG, NULL);
	(void)argv;
	(void)argc;
// Я хз як передавати параметри в Windows тому так. І потім це єдиний працюючий файл)
	file_parcing("scenes/working_test", &rt_data);
	ray_tracing(&rt_data);
	return (0);
}
