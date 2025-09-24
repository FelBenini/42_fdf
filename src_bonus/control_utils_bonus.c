/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:42:40 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/23 15:01:27 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	translate(int keycode, t_environment *env)
{
	if (keycode == 119)
		env->camera.offset_y -= 5;
	if (keycode == 115)
		env->camera.offset_y += 5;
	if (keycode == 100)
		env->camera.offset_x += 5;
	if (keycode == 97)
		env->camera.offset_x -= 5;
}

void	change_scale(int value, t_environment *env)
{
	if (value > 0)
	{
		if (env->scale == 0)
			env->scale -= 0.1;
		env->scale /= 1.1;
	}
	else
	{
		if (env->scale == 0)
			env->scale += 0.1;
		env->scale *= 1.1;
	}
	print_matrix(env);
}

void	update_cos_sin(t_environment *env)
{
	env->camera.x_cos = cos(env->camera.x_rotation);
	env->camera.x_sin = sin(env->camera.x_rotation);
	env->camera.y_cos = cos(env->camera.y_rotation);
	env->camera.y_sin = sin(env->camera.y_rotation);
	env->camera.z_cos = cos(env->camera.z_rotation);
	env->camera.z_sin = sin(env->camera.z_rotation);
}

int	rotate(int keycode, void *params)
{
	t_environment	*env;

	env = (t_environment *)params;
	if (keycode == 65362)
		env->camera.x_rotation += 0.05;
	if (keycode == 65364)
		env->camera.x_rotation -= 0.05;
	if (keycode == 65363)
		env->camera.y_rotation += 0.05;
	if (keycode == 65361)
		env->camera.y_rotation -= 0.05;
	update_cos_sin(env);
	print_matrix(env);
	return (0);
}
