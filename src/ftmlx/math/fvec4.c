/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 02:59:48 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/24 11:58:17 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libftmlx/math/ftmlx_vec.h"

float	fvec4_magn(t_fvec4 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

t_fvec4	fvec4_norm(t_fvec4 v)
{
	float	div_magn;

	div_magn = 1.0 / fvec4_magn(v);
	return ((t_fvec4){v.x * div_magn, v.y * div_magn,
		v.z * div_magn, v.w * div_magn});
}
