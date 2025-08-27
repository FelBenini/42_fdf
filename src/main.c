/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:48:48 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/27 12:52:11 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_mlx_args	mlx;
	t_img_data	img;

	img.width = 760;
	img.height = 680;
	if (argc != 2)
		return (ft_printf("Please, pass a map as an input"), 1);
	(void)argv;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, img.width, img.height, "HELLO WORLD");
	img.img = mlx_new_image(mlx.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	draw_line(&img, new_2dpoint(55, 5), new_2dpoint(155, 155));
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_destroy_image(mlx.mlx, img.img);
	mlx_hook(mlx.win, 17, 0, close_window, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
