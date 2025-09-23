/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:57:53 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/23 14:55:45 by fbenini-         ###   ########.fr       */
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
	t_environment	*env;

	env = (t_environment *)params;
	if (keycode == 65307)
	{
		mlx_loop_end(env->mlx.mlx);
		ft_printf("\n👋 Leaving now, bye!\n");
	}
	translate(keycode, env);
	handle_color_change(keycode, env);
	ft_printf("%d", keycode);
	if (keycode == 98)
		env->bending_factor += 0.1;
	if (keycode == 118)
		env->bending_factor -= 0.1;
	if (keycode == 91)
		env->z_factor -= 0.01;
	if (keycode == 93)
		env->z_factor += 0.01;
	rotate(keycode, params);
	return (0);
}
