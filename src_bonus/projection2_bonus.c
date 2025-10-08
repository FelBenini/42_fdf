/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:17:34 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/07 17:17:46 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_2dpoint	parallel_projection(t_3dpoint *point3d, t_environment *env,
							double x_val, double y_val)
{
	t_2dpoint	res;

	res.x = (int)(x_val * env->scale);
	res.y = (int)(y_val * env->scale);
	res.height = point3d->z;
	if (point3d->has_color)
		res.color = point3d->color;
	else
		res.color = get_color(res.height);
	res.x += env->offset_x + env->camera.offset_x;
	res.y += env->offset_y + env->camera.offset_y;
	return (res);
}

t_2dpoint	isometric_projection(t_3dpoint *point3d, double x_val,
							double y_val, double z_val)
{
	t_2dpoint		res;
	t_environment	*env;
	double			y_res;
	double			x_res;

	env = *get_env();
	x_res = (x_val - y_val) * 0.866;
	y_res = (x_val + 2 * y_val + -(z_val * 0.5)) * 0.5;
	x_res *= env->scale;
	y_res *= env->scale;
	res.height = point3d->z;
	if (point3d->has_color)
		res.color = point3d->color;
	else
		res.color = get_color(res.height);
	x_res += env->offset_x + env->camera.offset_x + 200;
	y_res += env->offset_y + env->camera.offset_y;
	res.x = x_res;
	res.y = y_res;
	return (res);
}
