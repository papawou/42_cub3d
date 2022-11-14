/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:57:18 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/14 12:52:57 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_UTILS_H
# define FTMLX_UTILS_H

# include <math.h>

# define PI 3.14159265358979323846

# include "libftmlx/math/ftmlx_vec.h"

double	ft_clamp(double min, double max, double value);
double	ft_lerp(double start, double end, double alpha);
double	ft_invlerp(double start, double end, double value);
double	ft_remap(t_fvec2 in, t_fvec2 out, double value);

double	deg_to_rad(double deg);
double	rad_to_deg(double rad);
int		ft_abs(int a);
double	ft_fabs(double a);

#endif