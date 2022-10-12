/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:12:46 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/12 11:46:33 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmlx/math/ftmlx_utils.h"

float	deg_to_rad(float deg)
{
	return (deg * PI / 180.0);
}

float	rad_to_deg(float rad)
{
	return (rad * 180.0 / PI);
}

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

double	ft_fabs(double a)
{
	if (a < 0.0)
		return (-a);
	else
		return (a);
}
