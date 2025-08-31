/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:33:51 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/28 13:33:56 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_environment	*init_environment(void)
{
	static t_environment	*env;

	if (env)
		return (env);
	env = ft_calloc(1, sizeof(t_environment));
	if (!env)
		return (NULL);
	env->img.width = 1920;
	env->img.height = 1080;
	env->mlx.mlx = mlx_init();
	env->mlx.win = mlx_new_window(env->mlx.mlx, env->img.width, env->img.height, "FDF");
	env->img.img = mlx_new_image(env->mlx.mlx, env->img.width, env->img.height);
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel,
			&env->img.line_length, &env->img.endian);
	return (env);
}
