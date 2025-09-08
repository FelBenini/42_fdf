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

#include "fdf.h"

static void	create_lines(t_3dpoint ***matrix, t_img_data *img_data,
						int i, int j)
{
	t_2dpoint	*point;
	t_2dpoint	*next_point;

	point = isometric_projection(matrix[i][j]);
	if (matrix[i][j + 1])
	{
		next_point = isometric_projection(matrix[i][j + 1]);
		draw_line(img_data, point, next_point, 0);
		free(next_point);
	}
	if (matrix[i + 1] && matrix[i + 1][j])
	{
		next_point = isometric_projection(matrix[i + 1][j]);
		draw_line(img_data, point, next_point, 0);
		free(next_point);
	}
	free(point);
}

void	print_matrix(t_3dpoint ***matrix, t_img_data *img_data)
{
	int			j;
	int			i;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			create_lines(matrix, img_data, i, j);
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_environment	*env;

	if (argc != 2)
		return (ft_printf("Please, pass a map as an input"), 1);
	if (!validate_input(argv[1]))
		return (1);
	env = init_environment(argv[1]);
	print_matrix(env->map, &env->img);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.win, env->img.img, 0, 0);
	mlx_hook(env->mlx.win, 17, 0, close_window, &env->mlx);
	mlx_key_hook(env->mlx.win, handle_keymaps, &env->mlx);
	mlx_loop(env->mlx.mlx);
	clean_env(env);
	return (0);
}
