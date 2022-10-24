/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:58:47 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/24 11:58:47 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libftmlx/math/ftmlx_vec.h"

t_fvec3	fvec3_inv(t_fvec3 v)
{
	return ((t_fvec3){-v.x, -v.y, -v.z});
}

t_fvec3	fvec3_add(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_fvec3	fvec3_minus(t_fvec3 a, t_fvec3 b)
{
	t_fvec3	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}
