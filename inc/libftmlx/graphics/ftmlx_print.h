/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:56:51 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/24 00:55:16 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_PRINT_H
# define FTMLX_PRINT_H

void	ftmlx_put_bresen_line(t_vec2 a, t_vec2 b, t_color c[2], t_img *canvas);
void	ftmlx_put_circle(t_vec2 pos, int rad, t_color c, t_img *canvas);

#endif