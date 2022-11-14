/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:56:48 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/14 12:49:01 by kmendes          ###   ########.fr       */
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

void	fix_padding_x(t_fvec2 *player_pos, t_fvec3 *incr_pos, t_scene *sc)
{
	double		mantissa;
	double		real;
	t_rayres	ray_res;

	ray_res = raycast(*player_pos, fvec2_norm((t_fvec2){incr_pos->x, 0}), sc);
	if (ray_res.z <= 0.11)
		incr_pos->x = 0;
	else if ((ray_res.z - 0.11) < ft_fabs(incr_pos->x))
	{
		if (incr_pos->x < 0.0)
			incr_pos->x = -(ray_res.z - 0.11);
		else
			incr_pos->x = ray_res.z - 0.11;
	}
	*player_pos = fvec2_add(*player_pos, (t_fvec2){incr_pos->x, 0});
	if ((int)player_pos->y == (int)sc->player.pos.y)
		return ;
	mantissa = modf(player_pos->x, &real);
	if (mantissa < 0.12)
		player_pos->x = real + 0.12;
	else if (mantissa > 0.88)
		player_pos->x = real + 0.88;
}

void	fix_padding_y(t_fvec2 *player_pos, t_fvec3 *incr_pos, t_scene *sc)
{
	double		mantissa;
	double		real;
	t_rayres	ray_res;

	ray_res = raycast(*player_pos, fvec2_norm((t_fvec2){0, incr_pos->y}), sc);
	if (ray_res.z <= 0.11)
		incr_pos->y = 0;
	else if ((ray_res.z - 0.11) < ft_fabs(incr_pos->y))
	{
		if (incr_pos->y < 0.0)
			incr_pos->y = -(ray_res.z - 0.11);
		else
			incr_pos->y = ray_res.z - 0.11;
	}
	*player_pos = fvec2_add(*player_pos, (t_fvec2){0, incr_pos->y});
	if ((int)player_pos->x == (int)sc->player.pos.x)
		return ;
	mantissa = modf(player_pos->y, &real);
	if (mantissa < 0.12)
		player_pos->y = real + 0.12;
	else if (mantissa > 0.89)
		player_pos->y = real + 0.88;
}

void	move_player(t_scene *sc, t_fvec2 move)
{
	t_fvec3	incr_pos;
	t_fvec2	player_pos;

	player_pos = sc->player.pos;
	incr_pos = quat_mult_vec(sc->player.rot, (t_fvec3){move.x, move.y, 0});
	if (incr_pos.x != 0.0)
		fix_padding_x(&player_pos, &incr_pos, sc);
	if (incr_pos.y != 0.0)
		fix_padding_y(&player_pos, &incr_pos, sc);
	sc->player.pos = player_pos;
}

void	rotate_player(t_scene *sc, t_quat rot)
{
	sc->player.rot = quat_mult(sc->player.rot, rot, 10);
}
