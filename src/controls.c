/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:53:46 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/06 16:27:03 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	controls_listener(int keycode, t_scene *sc)
{
 //+x_axis main dir
	static double move_speed = 0.04;
	static double	rot_deg_speed = 5;
	
	if (keycode == XK_LEFT)
		rotate_player(sc, axisg_to_quat((t_axisg){0, 0, rot_deg_speed, -1}));
	else if (keycode == XK_RIGHT)
		rotate_player(sc, axisg_to_quat((t_axisg){0, 0, rot_deg_speed, 1}));
	else if (keycode == XK_A)
		move_player(sc, (t_fvec2){0, -move_speed});
	else if (keycode == XK_D)
		move_player(sc, (t_fvec2){0, move_speed});
	else if (keycode == XK_W)
		move_player(sc, (t_fvec2){move_speed, 0});
	else if (keycode == XK_S)
		move_player(sc, (t_fvec2){-move_speed, 0});
	else if (keycode == XK_SPACE)
	{
	}
	return (0);
}
