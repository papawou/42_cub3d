/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:59:10 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/03 16:45:20 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libftmlx/math/ftmlx_vec.h"

t_fvec2	fvec2_add(t_fvec2 a, t_fvec2 b)
{
	return ((t_fvec2){a.x + b.x, a.y + b.y});
}

t_fvec2	fvec2_minus(t_fvec2 a, t_fvec2 b)
{
	return ((t_fvec2){a.x - b.x, a.y - b.y});
}

double	fvec2_magn(t_fvec2 v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

t_fvec2	fvec2_norm(t_fvec2 v)
{
	double	div_magn;

	div_magn = 1.0 / fvec2_magn(v);
	return ((t_fvec2){v.x * div_magn, v.y * div_magn});
}
