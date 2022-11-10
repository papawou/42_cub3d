/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:46:26 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/09 16:40:11 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_scene(t_scene *sc)
{
	clean_map(&sc->map);
	if (sc->ftmlx.mlx)
	{
		clean_atlas(sc->ftmlx.mlx, &sc->atlas);
		ftmlx_free_img(sc->ftmlx.mlx, sc->canvas);
		sc->canvas = NULL;
		ftmlx_free_img(sc->ftmlx.mlx, sc->minimap);
		sc->minimap = NULL;
		ftmlx_clean(&sc->ftmlx);
	}
}

void	init_scene(t_scene *sc)
{
	*sc = (t_scene){0};
	sc->player.pos = (t_fvec2){-1, -1};
	if (ftmlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, &sc->ftmlx))
	{
		print_error("init_scene: ftmlx_init");
		exit(1);
	}
	sc->canvas = ftmlx_new_img(sc->ftmlx.mlx, sc->ftmlx.wh.x, sc->ftmlx.wh.y);
	if (SCREEN_HEIGHT < SCREEN_WIDTH)
		sc->minimap = ftmlx_new_img(sc->ftmlx.mlx,
				SCREEN_HEIGHT / 4, SCREEN_HEIGHT / 4);
	else
		sc->minimap = ftmlx_new_img(sc->ftmlx.mlx,
				SCREEN_WIDTH / 4, SCREEN_WIDTH / 4);
	sc->atlas.floor = (t_color){0, 255, 255, 0};
	sc->atlas.ceil = (t_color){255, 178, 102, 0};
	if (sc->canvas == NULL || sc->minimap == NULL)
	{
		clean_scene(sc);
		print_error("init_scene: #1");
		exit(1);
	}
}

_Bool	check_scene(t_scene *sc)
{
	if (sc->player.pos.x < 0 || sc->player.pos.y < 0)
	{
		print_error("check_scene: player not found");
		return (false);
	}
	if (!check_map(sc->map.data, sc->map.len))
	{
		print_error("check_scene: check_map failed");
		return (false);
	}
	return (true);
}
