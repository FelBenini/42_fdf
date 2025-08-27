/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:57:53 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/27 12:51:32 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(void *params)
{
	t_mlx_args	*mlx;

	mlx = (t_mlx_args *)params;
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_loop_end(mlx->mlx);
	return (0);
}
