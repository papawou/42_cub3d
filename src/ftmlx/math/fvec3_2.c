/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvec3_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 02:59:48 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/24 11:57:36 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libftmlx/math/ftmlx_vec.h"

t_fvec3	fvec3_norm(t_fvec3 v)
{
	float	div_magn;

	div_magn = 1.0 / fvec3_magn(v);
	return ((t_fvec3){v.x * div_magn, v.y * div_magn, v.z * div_magn});
}

float	fvec3_dot(t_fvec3 a, t_fvec3 b)
{
	float	dot;
	float	magn_a;
	float	magn_b;

	magn_a = fvec3_magn(a);
	magn_b = fvec3_magn(b);
	dot = a.x * b.x + a.y * b.y + a.z * b.z;
	return ((dot / magn_a) / magn_b);
}

t_fvec3	fvec3_cross(t_fvec3 a, t_fvec3 b)
{
	t_fvec3	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}

float	fvec3_magn(t_fvec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
