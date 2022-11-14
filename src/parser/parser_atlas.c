/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_atlas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:22:53 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/14 12:46:04 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

_Bool	parse_atlas(t_scene *sc)
{
	sc->atlas.floor = (t_color){0, 255, 255, 0};
	sc->atlas.ceil = (t_color){255, 178, 102, 0};
	sc->atlas.tex = ftmlx_new_png_img(sc->ftmlx.mlx,
			"bin/tex/pillar.png");
	sc->atlas.tex_ea = ftmlx_new_png_img(sc->ftmlx.mlx,
			"bin/tex/bluestone.png");
	sc->atlas.tex_we = ftmlx_new_png_img(sc->ftmlx.mlx,
			"bin/tex/colorstone.png");
	sc->atlas.tex_no = ftmlx_new_png_img(sc->ftmlx.mlx,
			"bin/tex/purplestone.png");
	sc->atlas.tex_so = ftmlx_new_png_img(sc->ftmlx.mlx,
			"bin/tex/redbrick.png");
	return (true);
}
