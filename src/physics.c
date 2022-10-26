/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:04:06 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/26 13:57:36 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

void	raycast(t_scene *sc)
{
	int			i_y;
	int			i_x;
	
	t_fvec2	ray_dir = get_player_dir(sc);
	t_vec2	ray_start = (t_vec2){(int)sc->player.pos.x, (int)sc->player.pos.y};
	double	sx = sqrt(1 + pow((double)ray_dir.y / ray_dir.x, 2));
	double	sy = sqrt(1 + pow((double)ray_dir.x / ray_dir.y, 2));
	t_vec2	step = {1, 1};
	if (ray_dir.x < 0)
		step.x = -1;
	if (ray_dir.y < 0)
		step.y = -1;
	t_vec2 curr_cell = ray_start;
	i_y = 0;
	i_x = 0;

	while (sc->map.data[curr_cell.y][curr_cell.x] < 1 &&
		0 <= curr_cell.x && curr_cell.x < sc->map.len.x &&
		0 <= curr_cell.y && curr_cell.y < sc->map.len.y)
	{
		if (i_x * sx < i_y * sy)
		{
			curr_cell.x += step.x;
			++i_x;
		}
		else
		{
			++i_y;
			curr_cell.y += step.y;
		}
	}
	sc->map.data[curr_cell.y][curr_cell.x] = 2;
}
