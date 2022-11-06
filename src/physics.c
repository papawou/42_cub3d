/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:04:06 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/06 16:51:21 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

t_fvec3	raycast(t_fvec2 ray_start, t_fvec2 ray_dir, t_scene *sc)
{
	t_fvec2		s;
	t_fvec2		d;
	t_vec2		step;
	t_vec2		curr_cell;
	int				side;
	double			wall_dist;

	if (ray_dir.x == 0)
		d.x = 1e30;
	else
		d.x = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
		d.y = 1e30;
	else
		d.y = fabs(1 / ray_dir.y);
	step = (t_vec2){1, 1};
	curr_cell = (t_vec2){(int)ray_start.x, (int)ray_start.y};
	if (ray_dir.x < 0)
	{
		step.x = -1;
		s.x = (ray_start.x - curr_cell.x) * d.x;
	}
	else
	{
		step.x = 1;
		s.x = (curr_cell.x + 1 - ray_start.x) * d.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		s.y = (ray_start.y - curr_cell.y) * d.y;
	}
	else
	{
		step.y = 1;
		s.y = (curr_cell.y + 1 - ray_start.y) * d.y;
	}
	while (0 <= curr_cell.x && curr_cell.x < sc->map.len.x &&
		0 <= curr_cell.y && curr_cell.y < sc->map.len.y &&
		sc->map.data[curr_cell.y][curr_cell.x] == GROUND)
	{
		if (s.x < s.y)
		{
			s.x += d.x;
			curr_cell.x += step.x;
			side = 0;
		}
		else
		{
			s.y += d.y;
			curr_cell.y += step.y;
			side = 1;
		}
	}
	if (!side)
		wall_dist = s.x - d.x;
	else
		wall_dist = s.y - d.y;
	return ((t_fvec3) {curr_cell.x, curr_cell.y, wall_dist});
}
