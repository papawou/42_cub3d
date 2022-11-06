/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:50:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/06 16:54:32 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void render_raycast(t_scene *sc)
{
	int			x;
	t_fvec2	dir, ray_dir;
	double	cam_x;
	t_fvec3	plane;

	dir = get_player_dir(sc);
	plane = quat_mult_vec(sc->player.rot, (t_fvec3){0, 0.66, 0});
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cam_x = 2 * ((double) x / SCREEN_WIDTH) - 1;
		ray_dir.x = dir.x + plane.x * cam_x;
		ray_dir.y = dir.y + plane.y * cam_x;
		t_fvec3 ret = raycast(sc->player.pos, ray_dir, sc);
		sc->map.data[(int)ret.y][(int)ret.x] = 2;
		int lineHeight = (int)(SCREEN_HEIGHT / ret.z);
		if (ret.z <= 0)
		{
			ft_putstr_fd("ret.z <= 0\n", 1);
			++x;
			continue;
		}
    int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
    if(drawStart < 0)
			drawStart = 0;
    int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
    if(drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;
		t_color c = (t_color) { 255, 255,0 ,0};
		ftmlx_put_bresen_line((t_vec2){x, drawStart}, (t_vec2){x, drawEnd},
			(t_color[2]) {c, c}, sc->canvas);
		++x;
	}
}
