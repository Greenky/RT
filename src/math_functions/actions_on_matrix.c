/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_on_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:06:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 13:21:25 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

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

void			normalize_basis(t_coord_sys *a)
{
	a->b_x = normalize_vector(a->b_x);
	a->b_y = normalize_vector(a->b_y);
	a->b_z = normalize_vector(a->b_z);
}
