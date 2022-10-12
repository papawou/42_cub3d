/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_quat.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:12:12 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/12 11:46:33 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_QUAT_H
# define FTMLX_QUAT_H

# include "ftmlx/math/ftmlx_vec.h"
# include "ftmlx/math/ftmlx_mat.h"

typedef t_fvec4	t_quat;

t_quat	quat_norm(t_quat q);
t_quat	quat_mult(t_quat a, t_quat b, int norm);
t_mat4	quat_to_mat(t_quat q);
t_quat	quat_inv(t_quat q);
t_fvec3	quat_mult_vec(t_quat q, t_fvec3 v);
t_quat	quat_id(void);
#endif