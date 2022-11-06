/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:32:27 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/06 17:30:13 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define MINIMAP_TILE_SIZE_X 10

static t_color	get_tile_color(t_int_2d map, t_fvec2 pos)
{
	enum e_tile	tile;

	if (pos.x < 0 || map.len.x <= pos.x
		|| pos.y < 0 || map.len.y <= pos.y)
		return ((t_color){255, 20, 147, 0});
	tile = map.data[(int)pos.y][(int)pos.x];
	if (tile == EMPTY)
		return ((t_color){127, 127, 127, 0});
	else if (tile == GROUND)
		return ((t_color){0, 255, 0, 0});
	else if (tile == WALL)
		return ((t_color){210, 105, 30, 0});
	else if (tile == WALL_HIT)
		return ((t_color){0, 0, 255, 0});
	return ((t_color){255, 20, 147, 0});
}

static void	gen_minimap(t_scene *sc)
{
	t_fvec2	map_dst;
	t_faabb	box;
	t_color	pxl_color;
	double	ratio;
	double	max_x;
	t_vec2	pxl;

	ratio = (double)sc->minimap->height / sc->minimap->width;
	max_x = MINIMAP_TILE_SIZE_X;
	box = (t_faabb){
		.a = (t_fvec2){sc->player.pos.x - max_x,
		sc->player.pos.y - (ratio * max_x)},
		.b = (t_fvec2){sc->player.pos.x + max_x,
		sc->player.pos.y + (ratio * max_x)}
	};
	pxl = (t_vec2){0};
	while (pxl.y < sc->minimap->height)
	{
		pxl.x = 0;
		while (pxl.x < sc->minimap->width)
		{
			map_dst.x = ft_remap((t_fvec2){0, sc->minimap->width - 1},
					(t_fvec2){box.a.x, box.b.x}, pxl.x);
			map_dst.y = ft_remap((t_fvec2){0, sc->minimap->height - 1},
					(t_fvec2){box.a.y, box.b.y}, pxl.y);
			pxl_color = get_tile_color(sc->map, map_dst);
			ftmlx_img_set_pxl_color(sc->minimap, pxl.x, pxl.y,
				ftmlx_get_color_int(pxl_color));
			++pxl.x;
		}
		++pxl.y;
	}
}

void	render_minimap(t_scene *sc)
{
	t_fvec2	p_dir;

	gen_minimap(sc);
	ftmlx_put_circle((t_vec2){(sc->minimap->width / 2),
		(sc->minimap->height / 2)}, 5, (t_color){179, 229, 252, 0},
		sc->minimap);
	p_dir = get_player_dir(sc);
	p_dir.x *= 10;
	p_dir.y *= 10;
	ftmlx_put_bresen_line((t_vec2){sc->minimap->width / 2,
		sc->minimap->height / 2}, (t_vec2){(sc->minimap->width / 2) + p_dir.x,
		(sc->minimap->height / 2) + p_dir.y},
		(t_color[2]){{255, 255, 255, 0}, {255, 0, 255, 0}}, sc->minimap);
	ftmlx_img_put_img(sc->minimap, sc->canvas, 0, 0);
}
