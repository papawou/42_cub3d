/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:56:48 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/08 20:32:55 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#include <stdio.h>

t_fvec2	get_player_dir(t_scene *sc)
{
	t_fvec3	dir;

	dir = quat_mult_vec(sc->player.rot, (t_fvec3){1, 0, 0});
	return (fvec2_norm((t_fvec2){dir.x, dir.y}));
}

void	move_player(t_scene *sc, t_fvec2 move)
{
	t_fvec3	incr_pos;
	t_fvec4	ray_res;

	incr_pos = quat_mult_vec(sc->player.rot, (t_fvec3){move.x, move.y, 0});
	if (incr_pos.x != 0.0)
	{
		ray_res = raycast(sc->player.pos, fvec2_norm((t_fvec2){incr_pos.x, 0}), sc);
		if (ray_res.z <= 0.11)
			incr_pos.x = 0;
		else if ((ray_res.z - 0.11) < ft_fabs(incr_pos.x))
			incr_pos.x = ((incr_pos.x < 0.0) * (-1)
				+ (incr_pos.x >= 0.0) * 1) * (ray_res.z - 0.11);
	}
	if (incr_pos.y != 0.0)
	{
		ray_res = raycast(sc->player.pos, fvec2_norm((t_fvec2){0, incr_pos.y}), sc);
		if (ray_res.z <= 0.11)
			incr_pos.y = 0;
		else if ((ray_res.z) - 0.11 < ft_fabs(incr_pos.y))
			incr_pos.y = ((incr_pos.y < 0.0) * -1 +
				(incr_pos.y >= 0.0) * 1) * (ray_res.z - 0.11);
	}
	sc->player.pos = fvec2_add(sc->player.pos, (t_fvec2){incr_pos.x, incr_pos.y});
}

void	rotate_player(t_scene *sc, t_quat rot)
{
	sc->player.rot = quat_mult(sc->player.rot, rot, 1);
}
