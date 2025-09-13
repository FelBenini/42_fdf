/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:00:59 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/06 20:17:56 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	rotate_x_axis(double *y, double *z, double x_angle)
{
	double	temp_y;
	double	temp_z;

	temp_y = *y;
	temp_z = *z;
	*y = temp_y * cos(x_angle) - temp_z * sin(x_angle);
	*z = temp_y * sin(x_angle) + temp_z * cos(x_angle);
}

static void	rotate_y_axis(double *x, double *z, double y_angle)
{
	double	temp_x;
	double	temp_z;

	temp_x = *x;
	temp_z = *z;
	*x = temp_x * cos(y_angle) + temp_z * sin(y_angle);
	*z = -temp_x * sin(y_angle) + temp_z * cos(y_angle);
}

static void	rotate_z_axis(double *x, double *y, double z_angle)
{
	double	temp_x;
	double	temp_y;

	temp_x = *x;
	temp_y = *y;
	*x = temp_x * cos(z_angle) - temp_y * sin(z_angle);
	*y = temp_x * sin(z_angle) + temp_y * cos(z_angle);
}

t_2dpoint	isometric_projection(t_3dpoint *point3d)
{
	t_2dpoint		res;
	t_environment	*env;
	double			x_val;
	double			y_val;
	double			z_val;

	env = *get_env();
	x_val = point3d->x;
	y_val = point3d->y;
	z_val = -point3d->z * 0.5;
	rotate_x_axis(&y_val, &z_val, env->camera.x_rotation);
	rotate_y_axis(&x_val, &z_val, env->camera.y_rotation);
	rotate_z_axis(&x_val, &y_val, env->camera.z_rotation);
	res.x = (int)(x_val * env->scale);
	res.y = (int)(y_val * env->scale);
	res.height = point3d->z;
	if (point3d->color)
		res.color = ft_atoi_base(point3d->color, "0123456789ABCDEF");
	else
		res.color = get_color(res.height);
	res.x += env->offset_x;
	res.y += env->offset_y;
	return (res);
}
