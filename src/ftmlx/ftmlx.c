/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:03:38 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/22 21:37:36 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftmlx.h"

void	ftmlx_clean(t_ftmlx *ftmlx)
{
	if (ftmlx->mlx == NULL)
		return ;
	if (ftmlx->win)
		mlx_destroy_window(ftmlx->mlx, ftmlx->win);
	ftmlx->win = NULL;
	free(ftmlx->mlx);
	ftmlx->mlx = NULL;
}

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
