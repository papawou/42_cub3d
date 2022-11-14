/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:12:46 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/03 16:45:20 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmlx/math/ftmlx_utils.h"

double	deg_to_rad(double deg)
{
	return (deg * PI / 180.0);
}

double	rad_to_deg(double rad)
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
