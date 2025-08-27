/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:48:48 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/27 17:51:53 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_matrix(t_3dpoint ***matrix)
{
	int	j;
	int	i;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			ft_printf("x: %d y: %d z: %d\n", matrix[i][j]->x, matrix[i][j]->y, matrix[i][j]->z);
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
	print_matrix(matrix_3d);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, img.width, img.height, "HELLO WORLD");
	img.img = mlx_new_image(mlx.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_hook(mlx.win, 17, 0, close_window, &mlx);
	mlx_loop(mlx.mlx);
	mlx_destroy_window(mlx.mlx, mlx.win);
	clear_matrix(matrix_3d);
	return (0);
}
