/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:12:53 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/23 17:21:03 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmlx/math/ftmlx_vec.h"

float	ft_clamp(float min, float max, float value)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

float	ft_lerp(float start, float end, float alpha)
{
	return ((1 - alpha) * start + alpha * end);
}

float	ft_invlerp(float start, float end, float value)
{
	return ((value - start) / (end - start));
}

float	ft_remap(t_fvec2 in, t_fvec2 out, float value)
{
	return (ft_lerp(out.x, out.y, ft_invlerp(in.x, in.y, value)));
}
