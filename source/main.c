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

	rt->cl.err = clGetDeviceIDs(rt->cl.platform_id, CL_DEVICE_TYPE_DEFAULT,
								1, &rt->cl.device_id, &rt->cl.devices_num);

	rt->cl.context = clCreateContext(NULL, 1, &rt->cl.device_id, NULL,
									 NULL, &rt->cl.err);

	rt->cl.queue = clCreateCommandQueue(rt->cl.context, rt->cl.device_id,
										0, &rt->cl.err);

	rt->cl.program = clCreateProgramWithSource(rt->cl.context, 1,
											   (const char **)&src, (const size_t *)&src_size, &rt->cl.err);
//	ft_putendl("clCreateProgramWithSource done.");

	rt->cl.err = clBuildProgram(rt->cl.program, 1, &rt->cl.device_id, NULL,
										 NULL, NULL);

//	ft_putendl("clBuildProgram done.");
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
//	ft_putendl("clCreateKernel done.");
	free(src);
}

void	cl_start(t_rt *rt)
{
	rt->cl.objects = clCreateBuffer(rt->cl.context,CL_MEM_COPY_HOST_PTR,
									sizeof(t_objects) * rt->cl_data.num_of_objects,
									rt->objects_arr, &rt->cl.err);

	rt->cl.lights = clCreateBuffer(rt->cl.context, CL_MEM_COPY_HOST_PTR,
									sizeof(t_light) * rt->cl_data.num_of_lights,
									rt->lights_arr, &rt->cl.err);

	rt->cl.image = clCreateBuffer(rt->cl.context, CL_MEM_READ_WRITE,
								  sizeof(unsigned int) * SCR_SIZE * SCR_SIZE,  NULL, &rt->cl.err);

	rt->cl.err = clSetKernelArg(rt->cl.kernel, 0, sizeof(t_cl_data), &rt->cl_data);
	rt->cl.err = clSetKernelArg(rt->cl.kernel, 1, sizeof(cl_mem), (void *)&rt->cl.image);
	rt->cl.err = clSetKernelArg(rt->cl.kernel, 2, sizeof(cl_mem), (void *)&rt->cl.objects);
	rt->cl.err = clSetKernelArg(rt->cl.kernel, 3, sizeof(cl_mem), (void *)&rt->cl.lights);

	rt->cl.err = clEnqueueNDRangeKernel(rt->cl.queue, rt->cl.kernel, 2, NULL,
						   (size_t[3]){SCR_SIZE, SCR_SIZE, 0}, NULL, 0, NULL, NULL);
//	system("leaks RT");
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
	rt->cl.err = clEnqueueReadBuffer(rt->cl.queue, rt->cl.image, CL_TRUE, 0,
						sizeof(unsigned int) * SCR_SIZE * SCR_SIZE, (unsigned int *)rt->screen_surface->pixels, 0, NULL, NULL);

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
	clReleaseMemObject(rt->cl.lights);
	clReleaseMemObject(rt->cl.objects);
	clReleaseMemObject(rt->cl.image);
}

int			main(int argc, char **argv)
{
	argc = 1;
	argv = NULL;
	t_rt	rt_data;
//	if (argc < 2)
//		error_exit(NUM_OF_ARG, NULL);
//	(void)argv;
//	(void)argc;
// 	Я хз як передавати параметри в Windows тому так. І потім це єдиний працюючий файл)
	file_parcing("scenes/working_test", &rt_data);
	init_gui_bmps(&rt_data);
	init_foot_gui_bmps(&rt_data);
	rt_data.aliasing = 0;
	rt_data.filter = 1;
	rt_data.gui.filter_gui = 0;
	init_bar_positions(&rt_data);
//	cl_init(&rt_data);
	ray_tracing(&rt_data);
	return (0);
}
