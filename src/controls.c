/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:53:46 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/28 18:56:46 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	controls_listener(int keycode, t_scene *sc)
{
	if (keycode == XK_LEFT)
		rotate_player(sc, axisg_to_quat((t_axisg){0, 1, 0, 1}));
	else if (keycode == XK_RIGHT)
		rotate_player(sc, axisg_to_quat((t_axisg){0, 1, 0, -1}));
	else if (keycode == XK_A)
		move_player(sc, (t_fvec2){-1, 0});
	else if (keycode == XK_D)
		move_player(sc, (t_fvec2){1, 0});
	else if (keycode == XK_W)
		move_player(sc, (t_fvec2){0, -1});
	else if (keycode == XK_S)
		move_player(sc, (t_fvec2){0, 1});
	else if (keycode == XK_SPACE)
		debug_minimap(sc);

	return (0);
}
