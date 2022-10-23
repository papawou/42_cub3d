/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:32:27 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/23 23:33:56 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_color	get_tile_color(t_scene *sc, t_vec2 pos)
{
	enum e_tile	tile;

	if (pos.x < 0 || sc->map.len.x <= pos.x
		|| pos.y < 0 || sc->map.len.y <= pos.y)
		return ((t_color){255, 20, 147, 0});
	tile = sc->map.data[pos.y][pos.x];
	if (tile == EMPTY)
		return ((t_color){127, 127, 127, 0});
	else if (tile == GROUND)
		return ((t_color){0, 255, 0, 0});
	else if (tile == WALL)
		return ((t_color){210, 105, 30, 0});
	return ((t_color){255, 20, 147, 0});
}

void	gen_minimap(t_scene *sc)
{
	t_vec2	map_dst;
	t_faabb	box;
	t_aabb	box_dst;
	t_color	pxl_color;

	box = (t_faabb){.a = (t_fvec2){sc->player.pos.x - 3.0,
		sc->player.pos.y - 3.0},
		.b = (t_fvec2){sc->player.pos.x + 3.0, sc->player.pos.y + 3.0}};
	box_dst = (t_aabb){.a = (t_vec2){0, 0}, .b = (t_vec2){100, 100}};
	while (box_dst.a.y < box_dst.b.y)
	{
		box_dst.a.x = 0;
		while (box_dst.a.x < box_dst.b.x)
		{
			map_dst.x = ft_remap((t_fvec2){0, 99}, (t_fvec2){box.a.x, box.b.x},
					box_dst.a.x);
			map_dst.y = ft_remap((t_fvec2){0, 99}, (t_fvec2){box.a.y, box.b.y},
					box_dst.a.y);
			pxl_color = get_tile_color(sc, map_dst);
			ftmlx_img_set_pxl_color(sc->minimap, box_dst.a.x, box_dst.a.y,
				ftmlx_get_color_int(pxl_color));
			++box_dst.a.x;
		}
		++box_dst.a.y;
	}
}

void	render_minimap(t_scene *sc)
{
	gen_minimap(sc);
	ftmlx_img_put_img(sc->minimap, sc->canvas, 0, 0);
}
