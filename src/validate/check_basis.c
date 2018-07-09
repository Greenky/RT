/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_basis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 12:19:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 13:16:48 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void		check_basis_for_orthogonal(t_coord_sys *a)
{
	if (is_null_vec(a->b_x) || is_null_vec(a->b_y) || is_null_vec(a->b_z))
	{
		init_standart_coord_sys(a);
		return ;
	}
	a->b_x = normalize_vector(a->b_x);
	a->b_y = normalize_vector(a->b_y);
	if (vect_scalar_mult(a->b_x, a->b_y) == 0)
	{
		a->b_z = normalize_vector(a->b_z);
		if (!((vect_scalar_mult(a->b_x, a->b_z) == 0) &&
			vect_scalar_mult(a->b_y, a->b_z) == 0))
			a->b_z = cross_product(a->b_x, a->b_y);
	}
	else
	{
		a->b_y = make_orthogonal_from_vector(a->b_x, a->b_y);
		a->b_z = cross_product(a->b_x, a->b_y);
	}
}

t_vector	make_orthogonal_from_vector(t_vector a, t_vector b)
{
	if ((a.x == 0 && a.y == 0) || (a.x == 0 && a.z == 0) ||
			(a.y == 0 && a.z == 0))
	{
		b.x = (a.x == 0) ? b.x : 0;
		b.y = (a.y == 0) ? b.y : 0;
		b.z = (a.z == 0) ? b.z : 0;
	}
	else if (a.x == 0 || a.y == 0 || a.z == 0)
	{
		b.x = (a.x == 0) ? b.x : 0;
		b.y = (a.y != 0 && a.x != 0) ? -a.x * b.x / a.y : b.y;
		b.z = (a.z == 0) ? b.z : ((a.x * b.x + a.y * b.y) / -a.z);
	}
	else
		b.z = ((a.x * b.x + a.y * b.y) / -a.z);
	b = normalize_vector(b);
	return (b);
}

void		init_standart_coord_sys(t_coord_sys *a)
{
	a->b_x = (t_vector){1, 0, 0};
	a->b_y = (t_vector){0, -1, 0};
	a->b_z = (t_vector){0, 0, -1};
}

int			is_null_vec(t_vector a)
{
	if (a.x == 0 && a.y == 0 && a.z == 0)
		return (TRUE);
	else
		return (FALSE);
}

t_vector	cross_product(t_vector a, t_vector b)
{
	t_vector c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}
