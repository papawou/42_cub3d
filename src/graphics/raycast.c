/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:50:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/06 17:57:34 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_raycast(t_scene *sc)
{
	int		x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_fvec2	dir;
	t_fvec2	ray_dir;
	double	cam_x;
	t_fvec3	plane;
	t_fvec4	ret;
	t_color	c;

	dir = get_player_dir(sc);
	plane = quat_mult_vec(sc->player.rot, (t_fvec3){0, 0.9, 0});
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cam_x = 2 * ((double) x / SCREEN_WIDTH) - 1;
		ray_dir.x = dir.x + plane.x * cam_x;
		ray_dir.y = dir.y + plane.y * cam_x;
		ret = raycast(sc->player.pos, ray_dir, sc);
		sc->map.data[(int)ret.y][(int)ret.x] = 2;
		line_height = (int)(SCREEN_HEIGHT / ret.z);
		if (ret.z <= 0)
		{
			ft_putstr_fd("ret.z <= 0\n", 1);
			++x;
			continue ;
		}
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		c = (t_color){255, 255, 0, 0};
		ftmlx_put_bresen_line((t_vec2){x, draw_start}, (t_vec2){x, draw_end},
			(t_color[2]){c, c}, sc->canvas);
		++x;
	}
}
