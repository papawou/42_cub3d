/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:04:06 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/14 12:48:50 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

static t_fvec2	raycast_comp_d(t_fvec2 ray_dir)
{
	t_fvec2	d;

	if (ray_dir.x == 0)
		d.x = 1e30;
	else
		d.x = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
		d.y = 1e30;
	else
		d.y = fabs(1 / ray_dir.y);
	return (d);
}

typedef struct s_raycast_vars
{
	t_fvec2		s;
	t_fvec2		d;
	t_vec2		step;
	t_vec2		curr_cell;
}	t_raycast_vars;

void	raycast_comp_s(t_fvec2 ray_start, t_fvec2 ray_dir, t_raycast_vars *v)
{
	if (ray_dir.x < 0)
	{
		v->step.x = -1;
		v->s.x = (ray_start.x - v->curr_cell.x) * v->d.x;
	}
	else
	{
		v->step.x = 1;
		v->s.x = (v->curr_cell.x + 1 - ray_start.x) * v->d.x;
	}
	if (ray_dir.y < 0)
	{
		v->step.y = -1;
		v->s.y = (ray_start.y - v->curr_cell.y) * v->d.y;
	}
	else
	{
		v->step.y = 1;
		v->s.y = (v->curr_cell.y + 1 - ray_start.y) * v->d.y;
	}
}

t_raycast_vars	raycast_comp(t_fvec2 ray_start, t_fvec2 ray_dir)
{
	t_raycast_vars	v;

	v.d = raycast_comp_d(ray_dir);
	v.curr_cell = (t_vec2){(int)ray_start.x, (int)ray_start.y};
	v.step = (t_vec2){1, 1};
	raycast_comp_s(ray_start, ray_dir, &v);
	return (v);
}

static enum	e_card	retrieve_card(int side, t_fvec2 ray_dir)
{
	if (side == 0)
	{
		if (ray_dir.x < 0)
			return ((enum e_card)W);
		return ((enum e_card)E);
	}
	if (ray_dir.y < 0)
		return ((enum e_card)N);
	return ((enum e_card)S);
}

t_rayres	raycast(t_fvec2 ray_start, t_fvec2 ray_dir, t_scene *sc)
{
	t_raycast_vars	v;
	int				side;

	v = raycast_comp(ray_start, ray_dir);
	while (0 <= v.curr_cell.x && v.curr_cell.x < sc->map.len.x
		&& 0 <= v.curr_cell.y && v.curr_cell.y < sc->map.len.y
		&& sc->map.data[v.curr_cell.y][v.curr_cell.x] == GROUND)
	{
		if (v.s.x < v.s.y)
		{
			v.s.x += v.d.x;
			v.curr_cell.x += v.step.x;
			side = 0;
		}
		else
		{
			v.s.y += v.d.y;
			v.curr_cell.y += v.step.y;
			side = 1;
		}
	}
	return ((t_rayres){v.curr_cell.x, v.curr_cell.y,
		(side == 0) * (v.s.x - v.d.x) + (side == 1) * (v.s.y - v.d.y),
		retrieve_card(side, ray_dir)});
}
