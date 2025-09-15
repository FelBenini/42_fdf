/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:48:48 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/07 15:03:29 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	create_lines(t_3dpoint **matrix, t_img_data *img_data,
						int i)
{
	t_2dpoint	point;
	t_2dpoint	next_point;

	point = isometric_projection(matrix[i]);
	if (matrix[i]->next)
	{
		next_point = isometric_projection(matrix[i]->next);
		draw_line(img_data, point, next_point, 0);
	}
	if (matrix[i]->below)
	{
		next_point = isometric_projection(matrix[i]->below);
		draw_line(img_data, point, next_point, 0);
	}
}

void	print_matrix(t_environment *env)
{
	int			i;
	t_3dpoint	**matrix;

	i = 0;
	matrix = env->map;
	set_background(&env->img);
	while (matrix[i])
	{
		create_lines(matrix, &env->img, i);
		i++;
	}
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.win, env->img.img, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_environment	*env;

	if (argc != 2)
		return (ft_printf("Please, pass a map as an input"), 1);
	if (!validate_input(argv[1]))
		return (1);
	env = init_environment(argv[1]);
	print_matrix(env);
	mlx_do_key_autorepeaton(env->mlx.mlx);
	mlx_hook(env->mlx.win, 17, 0, close_window, &env->mlx);
	mlx_key_hook(env->mlx.win, handle_keymaps, &env->mlx);
	mlx_hook(env->mlx.win, 4, 1L << 2, handle_mouse, &env->mlx);
	mlx_hook(env->mlx.win, 6, 1L << 6, mouse_move, &env);
	mlx_loop(env->mlx.mlx);
	clean_env(env);
	return (0);
}
