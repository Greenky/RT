/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 21:20:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/16 12:56:22 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int		check_camera(int fd, char **line, t_scene_data *scene)
{
	if (check_existence_word(fd, line, "Camera:") == FALSE)
		return (FALSE);
	if (check_origin(fd, line, &(scene->camera.origin)) == FALSE)
		return (FALSE);
	if (check_basis(fd, line, &(scene->camera.basis)) == FALSE)
		return (FALSE);
	ft_memdel((void**)line);
	return (TRUE);
}

int		check_existence_word(int fd, char **line, char *word)
{
	if (get_next_line(fd, line) <= 0)
		return (FALSE);
	if (ft_strcmp(*line, word) != 0)
		return (FALSE);
	ft_memdel((void**)line);
	return (TRUE);
}

int		check_origin(int fd, char **line, t_vector *v)
{
	char *s;

	if (get_next_line(fd, line) <= 0)
		return (FALSE);
	if (ft_strncmp(*line, "origin = {", 10) != 0)
		return (FALSE);
	s = ft_find_after_c(*line, '{');
	if (check_vector(s, v) == FALSE)
		return (FALSE);
	ft_memdel((void**)line);
	return (TRUE);
}

int		check_vector(char *s, t_vector *v)
{
	if (s == NULL || *s == '\0')
		return (FALSE);
	v->x = ft_atoi(s);
	s = ft_find_after_c(s, ' ');
	if (s == NULL)
		return (FALSE);
	v->y = ft_atoi(s);
	s = ft_find_after_c(s, ' ');
	if (s == NULL)
		return (FALSE);
	v->z = ft_atoi(s);
	return (TRUE);
}

int		check_basis(int fd, char **line, t_coord_sys *basis)
{
	char *s;

	if (get_next_line(fd, line) <= 0)
		return (FALSE);
	if (ft_strncmp(*line, "basis = {", 9) != 0)
		return (FALSE);
	s = ft_find_after_c(*line, '{');
	if (check_vector(s, &(basis->b_x)) == FALSE)
		return (FALSE);
	s = ft_find_after_c(s, '{');
	if (check_vector(s, &(basis->b_y)) == FALSE)
		return (FALSE);
	s = ft_find_after_c(s, '{');
	if (check_vector(s, &(basis->b_z)) == FALSE)
		return (FALSE);
	ft_memdel((void**)line);
	check_basis_for_orthogonal(basis);
	return (TRUE);
}
