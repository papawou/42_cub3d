/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:04:06 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/28 22:31:44 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

static void	reset_raycast_case(t_int_2d *map)
{
	t_vec2 map_i;

	map_i = (t_vec2){0};
	while (map_i.y < map->len.y)
	{
		map_i.x = 0;
		while (map_i.x < map->len.x)
		{
			if (map->data[map_i.y][map_i.x] == 2)
				map->data[map_i.y][map_i.x] = 1;
			++map_i.x;
		}
		++map_i.y;
	}
}

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
	i_y = 1;
	i_x = 1;

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
			curr_cell.y += step.y;
			++i_y;
		}
	}
	reset_raycast_case(&sc->map);
	sc->map.data[curr_cell.y][curr_cell.x] = 2;
}
