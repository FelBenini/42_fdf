/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:48:48 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/28 13:41:31 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_matrix(t_3dpoint ***matrix, t_img_data *img_data)
{
	int			j;
	int			i;
	t_2dpoint	*point;
	t_2dpoint	*next_point;
	t_2dpoint	*point_below;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			point = isometric_projection(matrix[i][j], 15);
			if (matrix[i][j + 1])
			{
				point_below = isometric_projection(matrix[i][j + 1], 15);
				draw_line(img_data, point, point_below, 0);
				free(point_below);
			}
			if (matrix[i + 1] && matrix[i + 1][j])
			{
				next_point = isometric_projection(matrix[i + 1][j], 15);
				draw_line(img_data, point, next_point, 0);
				free(next_point);
			}
			free(point);
			j++;
		}
		i++;
	}
}

void	clear_matrix(t_3dpoint ***matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			free(matrix[i][j]);
			j++;
		}
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	main(int argc, char *argv[])
{
	t_mlx_args	mlx;
	t_img_data	img;
	t_3dpoint	***matrix_3d;

	img.width = 760;
	img.height = 680;
	if (argc != 2)
		return (ft_printf("Please, pass a map as an input"), 1);
	matrix_3d = parse_map(argv[1]);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, img.width, img.height, "HELLO WORLD");
	img.img = mlx_new_image(mlx.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	print_matrix(matrix_3d, &img);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_hook(mlx.win, 17, 0, close_window, &mlx);
	mlx_loop(mlx.mlx);
	mlx_destroy_window(mlx.mlx, mlx.win);
	clear_matrix(matrix_3d);
	return (0);
}
