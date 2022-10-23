/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:32:15 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/23 23:32:18 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_atlas(t_mlx mlx, t_atlas *atlas)
{
	ftmlx_free_img(mlx, atlas->text_ea);
	atlas->text_ea = NULL;
	ftmlx_free_img(mlx, atlas->text_no);
	atlas->text_no = NULL;
	ftmlx_free_img(mlx, atlas->text_so);
	atlas->text_so = NULL;
	ftmlx_free_img(mlx, atlas->text_we);
	atlas->text_we = NULL;
}
