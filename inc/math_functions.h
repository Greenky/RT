/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:57:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 13:21:25 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_FUNCTIONS_H
# define MATH_FUNCTIONS_H

float		find_square(float a);
float		distance(t_vector v1, t_vector v2);
float		length(t_vector v);

t_vector	vect_diff(t_vector v1, t_vector v2);
t_vector	vect_sum(t_vector v1, t_vector v2);
t_vector	vect_mult(t_vector v1, float multiplier);
float		vect_scalar_mult(t_vector v1, t_vector v2);
t_vector	normalize_vector(t_vector a);

t_vector	matrice_mult_vect(t_coord_sys a, t_vector v);
t_coord_sys	count_inverse_matrix(t_coord_sys a);
void		normalize_basis(t_coord_sys *a);

#endif
