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

#include "fdf.h"

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
	t_mlx_args	*mlx;

	mlx = (t_mlx_args *)params;
	if (keycode == 65307)
	{
		mlx_loop_end(mlx->mlx);
		ft_printf("\n👋 Leaving now, bye!\n");
	}
	return (0);
}
