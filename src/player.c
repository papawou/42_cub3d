/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:56:48 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/06 16:25:05 by kmendes          ###   ########.fr       */
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

	//collide ?
	incr_pos = quat_mult_vec(sc->player.rot, (t_fvec3){move.x, move.y, 0});
	sc->player.pos = fvec2_add(sc->player.pos,
		(t_fvec2){incr_pos.x, incr_pos.y});
}

void	rotate_player(t_scene *sc, t_quat rot)
{
	sc->player.rot = quat_mult(sc->player.rot, rot, 1);
}
