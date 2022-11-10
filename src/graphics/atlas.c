/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:32:15 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/09 11:11:10 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_atlas(t_mlx mlx, t_atlas *atlas)
{
	ftmlx_free_img(mlx, atlas->tex_ea);
	atlas->tex_ea = NULL;
	ftmlx_free_img(mlx, atlas->tex_no);
	atlas->tex_no = NULL;
	ftmlx_free_img(mlx, atlas->tex_so);
	atlas->tex_so = NULL;
	ftmlx_free_img(mlx, atlas->tex_we);
	atlas->tex_we = NULL;
}
