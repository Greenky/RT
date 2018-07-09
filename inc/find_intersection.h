/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersection.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:56:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:58:59 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_INTERSECTION_H
# define FIND_INTERSECTION_H

void	plane_find_closest_intersect(t_ray r, t_intersect *inter);

void	sphere_find_closest_intersect(t_ray r, t_intersect *inter);
float	find_sphere_discriminant(t_ray r, t_figure *fig, float coefficient[3]);
int		find_the_root(float coefficient[3], float discriminant, float t[2]);

void	cyl_find_closest_intersect(t_ray r, t_intersect *inter);
float	find_cyl_discriminant(t_ray r, float radius, float *coefficient);

void	cone_find_closest_intersect(t_ray r, t_intersect *inter);
float	find_cone_discriminant(t_ray r, float *coefficient, float coef);

#endif
