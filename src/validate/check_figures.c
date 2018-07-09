/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 21:31:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 14:21:05 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int		check_figure(int fd, char **line, t_figure *f, int fig_num)
{
	if (fig_num == 1)
	{
		if (check_existence_word(fd, line, "") == FALSE)
			return (FALSE);
		if (check_existence_word(fd, line, "Figures:") == FALSE)
			return (FALSE);
	}
	if (check_existence_word(fd, line, "***") == FALSE)
		return (FALSE);
	if (check_type_fig(fd, line, &(f->type)) == FALSE)
		return (FALSE);
	if (check_color(fd, line, &(f->color)) == FALSE)
		return (FALSE);
	if (check_origin(fd, line, &(f->origin)) == FALSE)
		return (FALSE);
	if (check_radius(fd, line, &(f->radius_or_cone_coef), f->type) == FALSE)
		return (FALSE);
	if (check_basis(fd, line, &(f->basis)) == FALSE)
		return (FALSE);
	if (check_bling_phong(fd, line, &(f->bling_phong)) == FALSE)
		return (FALSE);
	ft_memdel((void**)line);
	init_figure_functions(f, f->type);
	return (TRUE);
}

int		check_type_fig(int fd, char **line, int *type)
{
	char	*s;

	if (get_next_line(fd, line) <= 0)
		return (FALSE);
	if (ft_strncmp(*line, "type = ", 7) != 0)
		return (FALSE);
	s = ft_find_after_c(*line, '=');
	if (s == NULL || *s == '\0')
		return (FALSE);
	if (ft_strcmp(s, " SPHERE") == 0)
		*type = SPHERE;
	else if (ft_strcmp(s, " CYLINDER") == 0)
		*type = CYLINDER;
	else if (ft_strcmp(s, " CONE") == 0)
		*type = CONE;
	else if (ft_strcmp(s, " PLANE") == 0)
		*type = PLANE;
	else
		return (FALSE);
	ft_memdel((void**)line);
	return (TRUE);
}

int		check_radius(int fd, char **line, float *radius_or_cone_coef, int type)
{
	char	*s;

	if (get_next_line(fd, line) <= 0)
		return (FALSE);
	if (type == CONE)
	{
		if (ft_strncmp(*line, "cone_coef = ", 12) != 0)
			return (FALSE);
	}
	else
	{
		if (ft_strncmp(*line, "radius_or_cone_coef = ", 9) != 0)
			return (FALSE);
	}
	s = ft_find_after_c(*line, '=');
	*radius_or_cone_coef = atoif(s);
	if (*s <= 0 || *s >= 100)
		return (FALSE);
	else
	{
		ft_memdel((void**)line);
		return (TRUE);
	}
}

int		check_bling_phong(int fd, char **line, int *bling_phong)
{
	char	*s;

	if (get_next_line(fd, line) <= 0)
		return (FALSE);
	if (ft_strncmp(*line, "bling_phong = ", 14) != 0)
		return (FALSE);
	s = ft_find_after_c(*line, '=');
	*bling_phong = ft_atoi(s);
	if (*bling_phong > 100000)
		*bling_phong = 100000;
	ft_memdel((void**)line);
	if (*bling_phong < 1)
		return (FALSE);
	else
		return (TRUE);
}

void	init_figure_functions(t_figure *fig, int name)
{
	if (name == SPHERE)
	{
		fig->find_intersection = sphere_find_closest_intersect;
		fig->find_normal_to_figure = find_normal_to_sphere;
	}
	else if (name == CYLINDER)
	{
		fig->find_intersection = cyl_find_closest_intersect;
		fig->find_normal_to_figure = find_normal_to_cylinder;
	}
	else if (name == CONE)
	{
		fig->find_intersection = cone_find_closest_intersect;
		fig->find_normal_to_figure = find_normal_to_cone;
	}
	else if (name == PLANE)
	{
		fig->find_intersection = plane_find_closest_intersect;
		fig->find_normal_to_figure = find_normal_to_plane;
	}
}
