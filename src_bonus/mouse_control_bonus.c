/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:44:04 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/15 20:00:27 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	mouse_press(int key, int x, int y, void *param)
{
	t_environment	*env;

	env = (t_environment *)param;
	env->keys.last_x = x;
	env->keys.last_y = y;
	if (key == 5)
		change_scale(1, env);
	if (key == 4)
		change_scale(-1, env);
	if (key == 2)
		env->keys.scroll_pressed = 1;
	if (key == 3)
		env->keys.right_pressed = 1;
	return (0);
}

int	mouse_drop(int key, int x, int y, void *param)
{
	t_environment	*env;

	env = (t_environment *)param;
	env->keys.last_x = x;
	env->keys.last_y = y;
	if (key == 2)
		env->keys.scroll_pressed = 0;
	if (key == 3)
		env->keys.right_pressed = 0;
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_environment	*env;

	env = (t_environment *)param;
	if (env->keys.scroll_pressed)
	{
		env->camera.y_rotation -= (double)(env->keys.last_x - x) / 120;
		env->camera.x_rotation += (double)(env->keys.last_y - y) / 120;
		update_cos_sin(env);
		print_matrix(env);
	}
	if (env->keys.right_pressed)
	{
		env->camera.offset_x -= (double)(env->keys.last_x - x);
		env->camera.offset_y -= (double)(env->keys.last_y - y);
		print_matrix(env);
	}
	env->keys.last_x = x;
	env->keys.last_y = y;
	return (0);
}
