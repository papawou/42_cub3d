/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_vec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:13:33 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/06 10:48:45 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_VEC_H
# define FTMLX_VEC_H

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_vec4
{
	int	x;
	int	y;
	int	z;
	int	w;
}	t_vec4;

typedef struct s_fvec2
{
	double	x;
	double	y;
}	t_fvec2;

typedef struct s_fvec3
{
	double	x;
	double	y;
	double	z;
}	t_fvec3;

typedef struct s_fvec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_fvec4;

typedef struct s_faabb
{
	t_fvec2	a;
	t_fvec2	b;
}	t_faabb;

typedef struct s_aabb
{
	t_vec2	a;
	t_vec2	b;
}	t_aabb;

double	fvec4_magn(t_fvec4 v);
t_fvec4	fvec4_norm(t_fvec4 v);

t_fvec3	fvec3_inv(t_fvec3 v);
t_fvec3	fvec3_add(t_fvec3 a, t_fvec3 b);
double	fvec3_magn(t_fvec3 v);
t_fvec3	fvec3_norm(t_fvec3 v);
double	fvec3_dot(t_fvec3 a, t_fvec3 b);
t_fvec3	fvec3_cross(t_fvec3 a, t_fvec3 b);
t_fvec3	fvec3_minus(t_fvec3 a, t_fvec3 b);

t_fvec2	fvec2_add(t_fvec2 a, t_fvec2 b);
t_fvec2	fvec2_minus(t_fvec2 a, t_fvec2 b);
double	fvec2_magn(t_fvec2 v);
t_fvec2	fvec2_norm(t_fvec2 v);


t_vec2				vec2_add(t_vec2 a, t_vec2 b);
t_vec2				vec2_minus(t_vec2 a, t_vec2 b);
unsigned int	vec2_magn(t_vec2 v);

#endif