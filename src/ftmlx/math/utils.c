/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:12:53 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/03 16:45:20 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmlx/math/ftmlx_vec.h"

double	ft_clamp(double min, double max, double value)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

double	ft_lerp(double start, double end, double alpha)
{
	return ((1 - alpha) * start + alpha * end);
}

double	ft_invlerp(double start, double end, double value)
{
	return ((value - start) / (end - start));
}

double	ft_remap(t_fvec2 in, t_fvec2 out, double value)
{
	return (ft_lerp(out.x, out.y, ft_invlerp(in.x, in.y, value)));
}
