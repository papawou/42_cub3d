/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:32:27 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/09 16:42:37 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

typedef struct s_vars_gen_minimap
{
	t_fvec2	map_dst;
	t_faabb	box;
	t_color	pxl_color;
	double	ratio;
	double	max_x;
	t_vec2	pxl;
}	t_vars_gen_minimap;

static void	gen_minimap(t_scene *sc)
{
	t_vars_gen_minimap	v;

	v.ratio = (double)sc->minimap->height / sc->minimap->width;
	v.max_x = sc->minimap->width / 20;
	v.box = (t_faabb){.a = (t_fvec2){sc->player.pos.x - v.max_x,
		sc->player.pos.y - (v.ratio * v.max_x)},
		.b = (t_fvec2){sc->player.pos.x + v.max_x,
		sc->player.pos.y + (v.ratio * v.max_x)}};
	v.pxl = (t_vec2){0};
	while (v.pxl.y < sc->minimap->height)
	{
		v.pxl.x = 0;
		while (v.pxl.x < sc->minimap->width)
		{
			v.map_dst.x = ft_remap((t_fvec2){0, sc->minimap->width - 1},
					(t_fvec2){v.box.a.x, v.box.b.x}, v.pxl.x);
			v.map_dst.y = ft_remap((t_fvec2){0, sc->minimap->height - 1},
					(t_fvec2){v.box.a.y, v.box.b.y}, v.pxl.y);
			v.pxl_color = get_tile_color(sc->map, v.map_dst);
			ftmlx_img_set_pxl_color(sc->minimap, v.pxl.x, v.pxl.y,
				ftmlx_get_color_int(v.pxl_color));
			++v.pxl.x;
		}
		++v.pxl.y;
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
