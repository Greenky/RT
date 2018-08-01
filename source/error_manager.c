/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 14:18:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/07 14:18:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void	error_exit(int error_name, t_rt *rt_data)
{
	if (error_name == NUM_OF_ARG)
		ft_putstr_fd("Input must include one parameter\nUsage:"
							"./RT\t[scene] [-s]\n", 2);
	else if (error_name == ERROR)
		perror("RT");
	else if (error_name == CAM_ERROR)
	{
		ft_putendl("You have no camera, ma dudes");
		system("say \"You have no camera, ma dudes\"");
	}
	else if (error_name == LOAD_BMP_ERROR)
	{
		ft_putendl("SDL_LoadBMP failed: ");
		system("say \"SDL_LoadBMP failed\"");
		ft_putendl(SDL_GetError());
	}
	if (rt_data != NULL)
		freesher(rt_data->lights, rt_data->objects);
	exit(1);
}

void	freesher(t_light *light, t_objects *shapes)
{
	t_light		*step_light;
	t_objects	*step_shape;

	while (light)
	{
		step_light = light->next;
		free(light);
		light = step_light;
	}
	while (shapes)
	{
		step_shape = shapes->next;
		free(shapes);
		shapes = step_shape;
	}
}

void	error_caster(int line_number, char *s1, char *s2)
{
	ft_putstr("error in line ");
	ft_putnbr(line_number);
	ft_putstr("\n");
	ft_putstr(s1);
	ft_putstr("\"");
	ft_putstr(s2);
	ft_putendl("\"");
	exit(1);
}
