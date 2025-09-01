/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:33:51 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/01 17:56:41 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_highest_point(t_3dpoint ***map, t_environment **environment)
{
	int				i;
	int				j;
	t_environment	*env;

	i = 0;
	env = *environment;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j]->x > env->highest_x)
				env->highest_x = map[i][j]->x;
			if (map[i][j]->y > env->highest_y)
				env->highest_y = map[i][j]->y;
			if (map[i][j]->z > env->highest_z)
				env->highest_z = map[i][j]->z;
			if (map[i][j]-> z < env->lowest_z)
				env->lowest_z = map[i][j]->z;
			j++;
		}
		i++;
	}
}

static double	get_base_scale(t_environment **environment)
{
	double			scale;
	int				res;
	t_environment	*env;

	scale = 100;
	env = *environment;
	res = env->highest_y;
	if (env->highest_x > res)
		res = env->highest_x;
	if (env->highest_z > res)
		res = env->highest_z;
	scale /= res * 0.14;
	return (scale);
}

t_environment	**get_env(void)
{
	static t_environment	*env;

	if (env)
		return (&env);
	env = malloc(sizeof(t_environment));
	env->highest_x = 0;
	env->highest_y = 0;
	env->highest_z = 0;
	env->lowest_z = 0;
	if (!env)
		return (NULL);
	return (&env);
}

t_environment	*init_environment(char *filename)
{
	t_environment	*env;

	env = *get_env();
	if (!env)
		return (NULL);
	env->map = parse_map(filename);
	env->img.width = 1920;
	env->img.height = 1080;
	env->mlx.mlx = mlx_init();
	env->mlx.win = mlx_new_window(env->mlx.mlx, env->img.width,
			env->img.height, "FDF");
	env->img.img = mlx_new_image(env->mlx.mlx, env->img.width, env->img.height);
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel,
			&env->img.line_length, &env->img.endian);
	get_highest_point(env->map, &env);
	env->scale = get_base_scale(&env);
	return (env);
}
