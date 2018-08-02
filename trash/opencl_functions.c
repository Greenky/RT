/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:57:59 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/24 20:58:00 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_functions.h"

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(2);
}

void	cl_check_error_info(t_rt *rt)
{
	size_t	log_size;
	char	*log;

	if (rt->cl.err != CL_SUCCESS)
	{
		clGetProgramBuildInfo(rt->cl.program, rt->cl.device_id,
							  CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		log = (char *) malloc(log_size);
		clGetProgramBuildInfo(rt->cl.program, rt->cl.device_id,
							  CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		ft_putendl(log);
		free(log);
	}
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
	rt->cl.err = clBuildProgram(rt->cl.program, 1, &rt->cl.device_id, NULL,
								NULL, NULL);
	cl_check_error_info(rt);
	rt->cl.kernel = clCreateKernel(rt->cl.program, "renderer", &rt->cl.err);
	cl_check_error_info(rt);
	free(src);
}

void	cl_set_arguments(t_rt *rt)
{
	rt->cl.objects = clCreateBuffer(rt->cl.context,CL_MEM_COPY_HOST_PTR,
				sizeof(t_objects) * rt->cl_data.num_of_objects,
					rt->objects_arr, &rt->cl.err);
	rt->cl.lights = clCreateBuffer(rt->cl.context, CL_MEM_COPY_HOST_PTR,
				sizeof(t_light) * rt->cl_data.num_of_lights,
					rt->lights_arr, &rt->cl.err);
	rt->cl.image = clCreateBuffer(rt->cl.context, CL_MEM_READ_WRITE,
				sizeof(unsigned int) * WIN_SIZE * WIN_SIZE,  NULL, &rt->cl.err);
	rt->cl.err = clSetKernelArg(rt->cl.kernel, 0,
				sizeof(t_cl_data), &rt->cl_data);
	rt->cl.err = clSetKernelArg(rt->cl.kernel, 1,
				sizeof(cl_mem), (void *)&rt->cl.image);
	rt->cl.err = clSetKernelArg(rt->cl.kernel, 2,
								sizeof(cl_mem), (void *)&rt->cl.objects);
	rt->cl.err = clSetKernelArg(rt->cl.kernel, 3,
								sizeof(cl_mem), (void *)&rt->cl.lights);
	cl_check_error_info(rt);
}

void	cl_start(t_rt *rt)
{
	cl_set_arguments(rt);
	rt->cl.err = clEnqueueNDRangeKernel(rt->cl.queue, rt->cl.kernel, 2, NULL,
										(size_t[3]){WIN_SIZE, WIN_SIZE, 0}, NULL, 0, NULL, NULL);
	rt->cl.err = clEnqueueReadBuffer(rt->cl.queue, rt->cl.image, CL_TRUE, 0,
									 sizeof(unsigned int) * WIN_SIZE * WIN_SIZE,
									 (unsigned int *)rt->screen_surface->pixels, 0, NULL, NULL);
	cl_check_error_info(rt);
	clReleaseMemObject(rt->cl.lights);
	clReleaseMemObject(rt->cl.objects);
	clReleaseMemObject(rt->cl.image);
}
