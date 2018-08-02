/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_on_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 20:40:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/01 14:33:12 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_functions.h"

cl_float3		matrix_mult_vect(t_coord_sys a, cl_float3 v)
{
	cl_float3		new_v;

	new_v.x = a.b_x.x * v.x + a.b_y.x * v.y + a.b_z.x * v.z;
	new_v.y = a.b_x.y * v.x + a.b_y.y * v.y + a.b_z.y * v.z;
	new_v.z = a.b_x.z * v.x + a.b_y.z * v.y + a.b_z.z * v.z;
	return (new_v);
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

void			create_coord_system(t_coord_sys *basis, t_coord_sys *init_basis,
								cl_float3 *angle_rot)
{
	if (basis->b_z.x != basis->b_z.x ||
	(basis->b_z.x == 0 && basis->b_z.y == 0 && basis->b_z.z == 0))
		basis->b_z = VEC(0, 1, 0);
	basis->b_z = normalize_vector(basis->b_z);
	if (basis->b_z.x == 0 && basis->b_z.z == 0)
	{
		basis->b_y = VEC(1, 0, 0);
		basis->b_x = VEC(0, 0, 1);
	}
	else
	{
		basis->b_y = VEC(0, -1, 0);
		basis->b_x = vect_cross_product(basis->b_z, basis->b_y);
		basis->b_x = normalize_vector(basis->b_x);
		basis->b_y = vect_cross_product(basis->b_x, basis->b_z);
		basis->b_x = vect_mult_scalar(basis->b_x, -1);
	}
	*init_basis = *basis;
	if (angle_rot)
		*angle_rot = VEC(0, 0, 0);
}
