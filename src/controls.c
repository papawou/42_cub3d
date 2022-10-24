/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:53:46 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/24 13:57:37 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define XK_Q 12
#define XK_W 13
#define XK_E 14
#define XK_A 0
#define XK_S 1
#define XK_D 2

#define XK_LEFT 123
#define XK_RIGHT 124
#define XK_DOWN 125
#define XK_UP 126

#define XK_ESC 100

int	controls_listener(int keycode, t_scene *sc)
{
	if (keycode == XK_LEFT)
		rotate_player(sc, axisg_to_quat((t_axisg){0, 1, 0, 10}));
	else if (keycode == XK_RIGHT)
		rotate_player(sc, axisg_to_quat((t_axisg){0, 1, 0, -10}));
	else if (keycode == XK_A)
		move_player(sc, (t_fvec2){-0.5, 0});
	else if (keycode == XK_D)
		move_player(sc, (t_fvec2){0.5, 0});
	else if (keycode == XK_W)
		move_player(sc, (t_fvec2){0, -0.5});
	else if (keycode == XK_S)
		move_player(sc, (t_fvec2){0, 0.5});
	return (0);
}
