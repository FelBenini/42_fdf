/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:33:51 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/23 14:59:36 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	get_highest_point(t_3dpoint **map, t_environment **environment)
{
	int				i;
	t_environment	*env;

	i = 0;
	env = *environment;
	while (map[i])
	{
		if (map[i]->z > env->highest_z)
			env->highest_z = map[i]->z;
		if (map[i]-> z < env->lowest_z)
			env->lowest_z = map[i]->z;
		i++;
	}
	env->z_factor = 10.00 / (double)(env->highest_z - env->lowest_z);
	if (env->z_factor > 0.5)
		env->z_factor = 0.5;
	if (env->z_factor < 0.3)
		env->z_factor = 0.3;
}

void	get_highest_projections(t_3dpoint *point_3d)
{
	t_environment	*env;
	t_2dpoint		point_2d;

	env = *get_env();
	point_2d = isometric_projection(point_3d);
	if (env->highest_x > point_2d.x)
		env->highest_x = point_2d.x;
	if (env->lowest_x < point_2d.x)
		env->lowest_x = point_2d.x;
	if (env->highest_y > point_2d.y)
		env->highest_y = point_2d.y;
	if (env->lowest_y < point_2d.y)
		env->lowest_y = point_2d.y;
}

t_environment	**get_env(void)
{
	static t_environment	*env;

	if (env)
		return (&env);
	env = malloc(sizeof(t_environment));
	env->highest_x = 0;
	env->lowest_x = 0;
	env->highest_y = 0;
	env->lowest_y = 0;
	env->highest_z = 0;
	env->lowest_z = 0;
	env->offset_x = 0;
	env->offset_y = 0;
	env->colors[0] = 0x606060;
	env->colors[1] = 0xeaeaea;
	env->colors[2] = 0xffa85a;
	env->width = 0;
	env->height = 0;
	env->scale = 1.5;
	env->z_factor = 0.5;
	env->is_color_terrain = 0;
	env->bending_factor = 0;
	if (!env)
		return (NULL);
	return (&env);
}

void	init_structs(t_environment *env, char *filename)
{
	env->camera.x_cos = cos(0.0);
	env->camera.x_sin = sin(0.0);
	env->camera.z_cos = cos(0.0);
	env->camera.z_sin = sin(0.0);
	env->camera.y_cos = cos(0.0);
	env->camera.y_sin = sin(0.0);
	env->camera.x_rotation = 0.0;
	env->camera.y_rotation = 0.0;
	env->camera.z_rotation = 0.0;
	env->camera.offset_x = 0;
	env->camera.offset_y = 0;
	env->keys.last_x = 0;
	env->keys.last_y = 0;
	env->img.width = 1920;
	env->img.height = 1080;
	env->menu.height = 1080;
	env->menu.width = 280;
	env->map = parse_map(filename);
	env->mlx.mlx = mlx_init();
}

t_environment	*init_environment(char *filename)
{
	t_environment	*env;
	char			*title;

	env = *get_env();
	init_structs(env, filename);
	title = ft_strjoin("FDF - ", filename);
	env->mlx.win = mlx_new_window(env->mlx.mlx, env->img.width,
			env->img.height, title);
	env->img.img = mlx_new_image(env->mlx.mlx, env->img.width, env->img.height);
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel,
			&env->img.line_length, &env->img.endian);
	env->menu.img = mlx_new_image(env->mlx.mlx, env->menu.width,
			env->menu.height);
	env->menu.addr = mlx_get_data_addr(env->menu.img, &env->menu.bits_per_pixel,
			&env->menu.line_length, &env->menu.endian);
	get_highest_point(env->map, &env);
	normalize_map(env);
	if (env->highest_x - env->lowest_x < env->highest_y - env->lowest_y)
		env->scale = (1920 * 0.80) / (env->highest_x - env->lowest_x);
	else
		env->scale = (1080 * 0.80) / (env->highest_y - env->lowest_y);
	env->offset_x = (1620 - ((env->highest_x) * env->scale)) / 2;
	env->offset_y = (1040 - ((env->highest_y) * env->scale)) / 2;
	free(title);
	return (env);
}
