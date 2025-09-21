/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:48:48 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/18 18:54:20 by fbenini-         ###   ########.fr       */
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
	print_menu(env);
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
	mlx_mouse_get_pos(env->mlx.mlx, env->mlx.win,
		&env->keys.last_x, &env->keys.last_y);
	mlx_hook(env->mlx.win, 17, 0, close_window, &env->mlx);
	mlx_hook(env->mlx.win, 2, 1L << 0, handle_keymaps, env);
	mlx_hook(env->mlx.win, 4, 1L << 2, mouse_press, env);
	mlx_hook(env->mlx.win, 5, 1L << 3, mouse_drop, env);
	mlx_loop(env->mlx.mlx);
	clean_env(env);
	return (0);
}
