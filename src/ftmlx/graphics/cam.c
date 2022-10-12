/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 02:34:45 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/12 11:46:33 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ftmlx.h"

void	ftmlx_update_cam(t_ftcam *cam)
{
	cam->vp = mat_mult(cam->proj, transform_to_mat(transform_inv(cam->tranf)));
}

void	ftmlx_init_cam(t_transform tranf, t_mat4 proj, t_ftcam *cam)
{
	cam->tranf = tranf;
	cam->proj = proj;
	ftmlx_update_cam(cam);
}
