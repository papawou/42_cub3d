/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:59:10 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/24 13:55:17 by kmendes          ###   ########.fr       */
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
