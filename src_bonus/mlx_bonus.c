/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:57:53 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/27 15:56:32 by fbenini-         ###   ########.fr       */
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

int	handle_keymaps(int keycode, void *params)
{
	t_mlx_args		*mlx;
	t_environment	*env;

	mlx = (t_mlx_args *)params;
	env = *get_env();
	if (keycode == 65307)
	{
		mlx_loop_end(mlx->mlx);
		ft_printf("\n👋 Leaving now, bye!\n");
	}
	if (keycode == 65363)
		env->offset_x += 1;
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
			env-> scale += 0.1;
		env->scale *= 1.1;
	}
}

int	rotate(int keycode, void *params)
{
	t_mlx_args		*mlx;
	t_environment	*env;

	mlx = (t_mlx_args *)params;
	env = *get_env();
	(void)mlx;
	(void)keycode;
	if (keycode == 65362)
		env->camera.x_rotation += 0.1;
	if (keycode == 65364)
		env->camera.x_rotation -= 0.1;
	if (keycode == 65363)
		env->camera.y_rotation -= 0.1;
	if (keycode == 65361)
		env->camera.y_rotation += 0.1;
	print_matrix(env);
	return (0);
}

int	handle_mouse(int keycode, void *params)
{
	t_mlx_args		*mlx;
	t_environment	*env;

	mlx = (t_mlx_args *)params;
	(void)mlx;
	env = *get_env();
	if (keycode == 5)
		change_scale(1, env);
	if (keycode == 4)
		change_scale(-1, env);
	print_matrix(env);
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_environment	*env;

	env = (t_environment *)param;
	(void)env;
	(void)x;
	(void)y;
	return (0);
}
