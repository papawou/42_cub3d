/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:50:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/14 12:53:05 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
	lh.x = y start
	lh.y = y end
	lh.z = y height
*/
static t_vec3	calc_lh(double dist)
{
	t_vec3	lh;

	lh.z = (int)(SCREEN_HEIGHT / dist);
	lh.x = -lh.z / 2 + SCREEN_HEIGHT / 2;
	if (lh.x < 0)
		lh.x = 0;
	lh.y = lh.z / 2 + SCREEN_HEIGHT / 2;
	if (lh.y >= SCREEN_HEIGHT)
		lh.y = SCREEN_HEIGHT - 1;
	return (lh);
}

static	void	draw_floor_ceil(t_vec3 lh, int x, t_scene *sc)
{
	if (lh.x != 0)
		ftmlx_put_bresen_line((t_vec2){x, 0}, (t_vec2){x, lh.x - 1},
			(t_color[2]){sc->atlas.floor, sc->atlas.floor}, sc->canvas);
	if (lh.y <= SCREEN_HEIGHT - 2)
		ftmlx_put_bresen_line((t_vec2){x, lh.y + 1},
			(t_vec2){x, SCREEN_HEIGHT - 1},
			(t_color[2]){sc->atlas.ceil, sc->atlas.ceil}, sc->canvas);
}

static int	shader_pxl(int *c, t_scene *sc)
{
	(void) sc;
	return (*c);
}

static void	draw_stripe(t_rayres ray_res, t_fvec2 ray_dir, t_vec2 pxl,
		t_scene *sc)
{
	t_vec3	lh;
	t_img	*tex;
	double	step;
	double	texacc;
	t_vec2	texpos;

	lh = calc_lh(ray_res.z);
	tex = get_tex(ray_res.card, (t_vec2){ray_res.x, ray_res.y}, &sc->atlas);
	texpos.x = get_texpos_x(ray_res, ray_dir, tex, sc);
	step = (double)tex->height / lh.z;
	texacc = (lh.x - SCREEN_HEIGHT / 2 + lh.z / 2) * step;
	pxl.y = lh.x;
	while (pxl.y <= lh.y)
	{
		texpos.y = (int)texacc & (tex->height - 1);
		ftmlx_img_set_pxl_color(sc->canvas, pxl.x, pxl.y,
			shader_pxl(ftmlx_img_get_pxl(tex, (int)texpos.x, (int)texpos.y),
				sc));
		texacc += step;
		++pxl.y;
	}
	draw_floor_ceil(lh, pxl.x, sc);
}

void	render_raycast(t_scene *sc)
{
	int			x;
	t_fvec2		dir;
	t_fvec2		ray_dir;
	t_fvec3		plane;
	t_rayres	ret;

	dir = get_player_dir(sc);
	plane = quat_mult_vec(sc->player.rot, (t_fvec3){0, 0.66, 0});
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_dir.x = dir.x + plane.x * (2 * ((double) x / SCREEN_WIDTH) - 1);
		ray_dir.y = dir.y + plane.y * (2 * ((double) x / SCREEN_WIDTH) - 1);
		ret = raycast(sc->player.pos, ray_dir, sc);
		sc->map.data[ret.y][ret.x] = 2;
		draw_stripe(ret, ray_dir, (t_vec2){x, 0}, sc);
		++x;
	}
}
