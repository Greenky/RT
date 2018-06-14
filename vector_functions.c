/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 13:13:39 by vmazurok          #+#    #+#             */
/*   Updated: 2018/06/01 13:13:41 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

t_vector	vec_dob(t_vector v1, t_vector v2)
{
	double		i;
	double		j;
	double		k;

	i = (v1.y * v2.z) - (v2.y * v1.z);
	j = -((v1.x * v2.z) - (v2.x * v1.z));
	k = (v1.x * v2.y) - (v2.x * v1.y);
	return (set_vector(i, j, k));
}

t_vector	set_vector(double x, double y, double z)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	v_to_len(t_vector v, double len, int norm)
{
	double mod;

	if (!norm)
	{
		mod = v_mod(v);
		v.x = v.x / mod * len;
		v.y = v.y / mod * len;
		v.z = v.z / mod * len;
	}
	else
	{
		v.x = v.x * len;
		v.y = v.y * len;
		v.z = v.z * len;
	}
	return (v);
}

t_vector	add_vectors(t_vector v1, t_vector v2)
{
	t_vector sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}

t_vector	sub_vectors(t_vector v1, t_vector v2)
{
	t_vector sub;

	sub.x = v1.x - v2.x;
	sub.y = v1.y - v2.y;
	sub.z = v1.z - v2.z;
	return (sub);
}
