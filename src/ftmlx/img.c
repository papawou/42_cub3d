/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:03:47 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/10 14:09:44 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftmlx.h"

void	ftmlx_free_img(t_mlx mlx, t_img *img)
{
	if (img == NULL)
		return ;
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	free(img);
}

int	*ftmlx_img_get_pxl(t_img *img, int x, int y)
{
	if (img->height <= y || img->width <= x || x < 0 || y < 0)
		return (NULL);
	return ((int *)(img->addr + (img->size_line * y + x * (img->bpp / 8))));
}

void	ftmlx_img_set_pxl_color(t_img *img, int x, int y, int color)
{
	int	i;
	int	pos;

	if (img->height <= y || img->width <= x || x < 0 || y < 0)
		return ;
	color = ftmlx_get_color_value(NULL, color);
	pos = (img->size_line * y + x * (img->bpp / 8));
	i = 0;
	while (i < (img->bpp / 8))
	{
		if (!img->endian)
			img->addr[pos + i] = (color >> (i * 8)) & 0xFF;
		else
			img->addr[pos + i] = (color >> ((sizeof(int) - 1 - i) * 8)) & 0xFF;
		++i;
	}
}
