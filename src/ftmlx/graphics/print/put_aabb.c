/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_aabb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:28:10 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/31 21:59:21 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmlx.h"

void	ftmlx_put_aabb(t_aabb box, t_color c, t_img *canvas)
{
	int tmp;

	tmp = box.a.x;
	while (box.a.y <  box.b.y)
	{
		box.a.x = tmp;
		while (box.a.x < box.b.x)
		{
			ftmlx_img_set_pxl_color(canvas, box.a.x, box.a.y, ftmlx_get_color_int(c));
			++box.a.x;
		}
		++box.a.y;
	}
}
