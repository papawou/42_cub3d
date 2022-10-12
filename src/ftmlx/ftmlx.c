/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:03:38 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/12 11:46:33 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftmlx.h"

int	ftmlx_init(int width, int height, t_ftmlx *ftmlx)
{
	ftmlx->mlx = mlx_init();
	if (ftmlx->mlx == NULL)
		return (1);
	ftmlx->win = mlx_new_window(ftmlx->mlx, width, height, "window");
	if (ftmlx->win == NULL)
		return (1);
	ftmlx->wh = (t_vec2){width, height};
	return (0);
}
