/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 00:24:35 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/24 11:11:29 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmlx.h"

static int	ftmlx_check_box(t_aabb *box, int width, int height)
{
	if (width <= box->a.x || box->b.x < 0 || height <= box->a.y || box->b.y < 0)
		return (0);
	if (box->a.x < 0)
		box->a.x = 0;
	if (box->a.y < 0)
		box->a.y = 0;
	if (width < box->b.x)
		box->b.x = width;
	if (height < box->b.y)
		box->b.y = height;
	return (1);
}

void	ftmlx_put_circle(t_vec2 pos, int rad, t_color c, t_img *canvas)
{
	float	dst;
	t_aabb	box;

	box = (t_aabb){.a = {pos.x - rad, pos.y - rad},
		.b = {pos.x + rad, pos.y + rad}};
	if (!ftmlx_check_box(&box, canvas->width, canvas->height))
		return ;
	while (box.a.y < box.b.y)
	{
		box.a.x = 0;
		while (box.a.x < box.b.x)
		{
			dst = sqrt(pow(box.a.x - pos.x, 2) + pow(box.a.y - pos.y, 2));
			if (dst < rad)
				ftmlx_img_set_pxl_color(canvas, box.a.x, box.a.y,
					ftmlx_get_color_int(c));
			++box.a.x;
		}
		++box.a.y;
	}
}
