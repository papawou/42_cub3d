/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:48:18 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/14 12:48:18 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_texpos_x(t_rayres ray_res, t_fvec2 ray_dir, t_img *tex,
		t_scene *sc)
{
	double	wall_x;
	int		tex_x;

	if (ray_res.card & WE)
		wall_x = sc->player.pos.y + ray_res.z * ray_dir.y;
	else
		wall_x = sc->player.pos.x + ray_res.z * ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * sc->atlas.tex->width;
	if (ray_res.card & WE && ray_dir.x < 0)
		tex_x = sc->atlas.tex->width - tex_x - 1;
	if (ray_res.card & NS && ray_dir.y > 0)
		tex_x = sc->atlas.tex->width - tex_x - 1;
	return (tex_x);
}

t_img	*get_tex(enum e_card card, t_vec2 cell, t_atlas *atlas)
{
	if (card == N)
		return (atlas->tex_no);
	if (card == S)
		return (atlas->tex_so);
	if (card == E)
		return (atlas->tex_ea);
	if (card == W)
		return (atlas->tex_we);
	return (atlas->tex);
}
