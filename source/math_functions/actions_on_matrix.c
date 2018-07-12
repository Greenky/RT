/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_on_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 20:40:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/09 20:40:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

t_vector		matrice_mult_vect(t_coord_sys a, t_vector v)
{
	t_vector		new_v;

	new_v.x = a.b_x.x * v.x + a.b_y.x * v.y + a.b_z.x * v.z;
	new_v.y = a.b_x.y * v.x + a.b_y.y * v.y + a.b_z.y * v.z;
	new_v.z = a.b_x.z * v.x + a.b_y.z * v.y + a.b_z.z * v.z;
	return (new_v);
}

t_coord_sys		count_inverse_matrix(t_coord_sys a)
{
	float		determinant;
	t_coord_sys	m;

	determinant = a.b_x.x * (a.b_y.y * a.b_z.z - a.b_z.y * a.b_y.z) -
				  a.b_y.x * (a.b_x.y * a.b_z.z - a.b_z.y * a.b_x.z) +
				  a.b_z.x * (a.b_x.y * a.b_y.z - a.b_y.y * a.b_x.z);
	determinant = 1 / determinant;
	m.b_x.x = (a.b_y.y * a.b_z.z - a.b_z.y * a.b_y.z) * determinant;
	m.b_x.y = (a.b_z.y * a.b_x.z - a.b_x.y * a.b_z.z) * determinant;
	m.b_x.z = (a.b_x.y * a.b_y.z - a.b_y.y * a.b_x.z) * determinant;
	m.b_y.x = (a.b_z.x * a.b_y.z - a.b_y.x * a.b_z.z) * determinant;
	m.b_y.y = (a.b_x.x * a.b_z.z - a.b_z.x * a.b_x.z) * determinant;
	m.b_y.z = (a.b_y.x * a.b_x.z - a.b_x.x * a.b_y.z) * determinant;
	m.b_z.x = (a.b_y.x * a.b_z.y - a.b_z.x * a.b_y.y) * determinant;
	m.b_z.y = (a.b_z.x * a.b_x.y - a.b_x.x * a.b_z.y) * determinant;
	m.b_z.z = (a.b_x.x * a.b_y.y - a.b_y.x * a.b_x.y) * determinant;
	return (m);
}

t_coord_sys		matrix_mult_matrix(t_coord_sys a, t_coord_sys b)
{
	t_coord_sys		new;

	new.b_x.x = a.b_x.x * b.b_x.x + a.b_y.x * b.b_x.y + a.b_z.x * b.b_x.z;
	new.b_x.y = a.b_x.y * b.b_x.x + a.b_y.y * b.b_x.y + a.b_z.y * b.b_x.z;
	new.b_x.z = a.b_x.z * b.b_x.x + a.b_y.z * b.b_x.y + a.b_z.z * b.b_x.z;

	new.b_y.x = a.b_x.x * b.b_y.x + a.b_y.x * b.b_y.y + a.b_z.x * b.b_y.z;
	new.b_y.y = a.b_x.y * b.b_y.x + a.b_y.y * b.b_y.y + a.b_z.y * b.b_y.z;
	new.b_y.z = a.b_x.z * b.b_y.x + a.b_y.z * b.b_y.y + a.b_z.z * b.b_y.z;

	new.b_z.x = a.b_x.x * b.b_z.x + a.b_y.x * b.b_z.y + a.b_z.x * b.b_z.z;
	new.b_z.y = a.b_x.y * b.b_z.x + a.b_y.y * b.b_z.y + a.b_z.y * b.b_z.z;
	new.b_z.z = a.b_x.z * b.b_z.x + a.b_y.z * b.b_z.y + a.b_z.z * b.b_z.z;

	return (new);
}

void			normalize_basis(t_coord_sys *a)
{
	a->b_x = normalize_vector(a->b_x);
	a->b_y = normalize_vector(a->b_y);
	a->b_z = normalize_vector(a->b_z);
}
