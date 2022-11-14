/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:46:08 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/06 17:03:46 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#include <stdio.h>

void	tostring_map(t_int_2d *map)
{
	t_vec2	i;

	i = (t_vec2){0};
	while (i.y < map->len.y)
	{
		i.x = 0;
		while (i.x < map->len.x)
		{
			printf("%d ", map->data[i.y][i.x]);
			++i.x;
		}
		printf("\n");
		++i.y;
	}
}

void	clean_map(t_int_2d *map)
{
	int	i;

	if (map->data == NULL)
		return ;
	i = 0;
	while (i < map->len.y)
	{
		free(map->data[i]);
		++i;
	}
	free(map->data);
	map->data = NULL;
}

void	reset_map(t_int_2d map, _Bool only_wall)
{
	t_vec2	map_i;

	map_i = (t_vec2){0};
	while (map_i.y < map.len.y)
	{
		map_i.x = 0;
		while (map_i.x < map.len.x)
		{
			if (only_wall)
			{
				if (map.data[map_i.y][map_i.x] == WALL_HIT)
					map.data[map_i.y][map_i.x] = WALL;
			}		
			else
				map.data[map_i.y][map_i.x] = EMPTY;
			++map_i.x;
		}
		++map_i.y;
	}
}

int	**create_map(t_vec2 map_size)
{
	int	**map;
	int	i;

	if (map_size.y <= 0 || map_size.x <= 0)
	{
		print_error("create_map: map_size incorrect");
		return (false);
	}
	map = (int **)malloc(sizeof(int *) * map_size.y);
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < map_size.y)
	{
		map[i] = malloc(sizeof(int) * map_size.x);
		if (map[i] == NULL)
		{
			while (i--)
				free(map[i]);
			return (NULL);
		}
		++i;
	}
	reset_map((t_int_2d){.len = map_size, .data = map}, false);
	return (map);
}
