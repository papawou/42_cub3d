/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:50:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/10 00:51:58 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
static t_color	get_tex_color(double ratio)
{
	
}

static void	draw_wall(t_fvec4 ray_res, t_fvec2 ray_dir, t_vec2 y, t_scene *sc)
{
	double	wall_x;
	int			tex_x;
	int			tex_w = sc->atlas.tex->width;

	if (ray_res.w == 0)
		wall_x = sc->player.pos.y + ray_res.z * ray_dir.y;
  else
		wall_x = sc->player.pos.x + ray_res.z * ray_dir.x;
  wall_x -= floor(wall_x);

	tex_x = wall_x * tex_w;
  if(ray_res.w == 0 && ray_dir.x > 0) //right to left
		tex_x = tex_w - tex_x - 1;
  if(ray_res.w == 1 && ray_dir.y < 0)
		tex_x = tex_w - tex_x - 1;
	
	int	pxl_x;

	pxl_x = y.x;
	while (pxl_x < y.y)
	{
		get_tex_color(pxl_x / )
	}
}
*/

static void	draw_stripe(t_fvec4 ray_res, t_fvec2 ray_dir, int x, t_scene *sc)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_color		c;

	(void) ray_dir;
	line_height = (int)(SCREEN_HEIGHT / ray_res.z);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	c = (t_color){255, 255, 0, 0};
	ftmlx_put_bresen_line((t_vec2){x, draw_start}, (t_vec2){x, draw_end},
		(t_color[2]){c, c}, sc->canvas);
	if (draw_start != 0)
		ftmlx_put_bresen_line((t_vec2){x, 0}, (t_vec2){x, draw_start - 1},
			(t_color[2]){sc->atlas.floor, sc->atlas.floor}, sc->canvas);
	if (draw_end <= SCREEN_HEIGHT - 2)
		ftmlx_put_bresen_line((t_vec2){x, draw_end + 1},
			(t_vec2){x, SCREEN_HEIGHT - 1},
			(t_color[2]){sc->atlas.ceil, sc->atlas.ceil}, sc->canvas);
}

void	render_raycast(t_scene *sc)
{
	int		x;
	t_fvec2	dir;
	t_fvec2	ray_dir;
	t_fvec3	plane;
	t_fvec4	ret;

	dir = get_player_dir(sc);
	plane = quat_mult_vec(sc->player.rot, (t_fvec3){0, 0.66, 0});
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_dir.x = dir.x + plane.x * (2 * ((double) x / SCREEN_WIDTH) - 1);
		ray_dir.y = dir.y + plane.y * (2 * ((double) x / SCREEN_WIDTH) - 1);
		ret = raycast(sc->player.pos, ray_dir, sc);
		if (ret.z <= 0)
			pause();
		sc->map.data[(int)ret.y][(int)ret.x] = 2;
		draw_stripe(ret, ray_dir, x, sc);
		++x;
	}
}
