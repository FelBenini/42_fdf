/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:33:23 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/07 15:14:42 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	clear_matrix(t_3dpoint **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]->color);
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	clear_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	clean_env(t_environment *env)
{
	mlx_destroy_image(env->mlx.mlx, env->img.img);
	mlx_destroy_window(env->mlx.mlx, env->mlx.win);
	mlx_destroy_display(env->mlx.mlx);
	clear_matrix(env->map);
	free(env->mlx.mlx);
	free(env);
}
