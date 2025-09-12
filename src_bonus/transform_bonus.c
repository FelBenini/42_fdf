/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:20:05 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/11 14:31:18 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	rotate_x(t_3dpoint *point, t_environment *env)
{
	double		angle;
	t_3dpoint	old_point;

	old_point = *point;
	angle = env->camera.x_rotation * (M_PI / 180.0);
	point->y = (old_point.y * cos(angle)) - (old_point.z * sin(angle));
	point->z = (old_point.y * sin(angle)) + (old_point.z * cos(angle));
}

void	rotate_y(t_3dpoint *point, t_environment *env)
{
	double		angle;
	t_3dpoint	old_point;

	old_point = *point;
	angle = env->camera.y_rotation * (M_PI / 180.0);
	point->x = (old_point.x * cos(angle)) + (old_point.z * sin(angle));
	point->z = (-old_point.x * sin(angle)) + (old_point.z * cos(angle));
}

void	rotate_z(t_3dpoint *point, t_environment *env)
{
	double	angle;
	t_3dpoint	old_point;

	old_point = *point;
	angle = env->camera.z_rotation * (M_PI / 180.0);
	point->x = (old_point.x * cos(angle)) - (old_point.y * sin(angle));
	point->y = (old_point.x * sin(angle)) + (old_point.y * cos(angle));
}

t_3dpoint	*transform_point(t_3dpoint *old_point)
{
	t_3dpoint		*res_point;
	t_environment	*env;

	res_point = malloc(sizeof(t_3dpoint));
	res_point->x = old_point->x;
	res_point->y = old_point->y;
	res_point->z = old_point->z;
	res_point->color = old_point->color;
	env = *get_env();
	rotate_z(res_point, env);
	rotate_x(res_point, env);
	rotate_y(res_point, env);
	return (res_point);
}
