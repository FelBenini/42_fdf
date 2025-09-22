/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:57:53 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/15 20:01:06 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	close_window(void *params)
{
	t_mlx_args	*mlx;

	mlx = (t_mlx_args *)params;
	mlx_loop_end(mlx->mlx);
	ft_printf("\n👋 Leaving now, bye!\n");
	return (0);
}

void	translate(int keycode, t_environment *env)
{
	if (keycode == 119)
		env->offset_y -= 5;
	if (keycode == 115)
		env->offset_y += 5;
	if (keycode == 100)
		env->offset_x += 5;
	if (keycode == 97)
		env->offset_x -= 5;
}

int	handle_keymaps(int keycode, void *params)
{
	t_environment	*env;

	env = (t_environment *)params;
	if (keycode == 65307)
	{
		mlx_loop_end(env->mlx.mlx);
		ft_printf("\n👋 Leaving now, bye!\n");
	}
	if (keycode == 65363)
		env->offset_x += 1;
	translate(keycode, env);
	rotate(keycode, params);
	return (0);
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
}

static void	update_cos_sin(t_environment *env)
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
