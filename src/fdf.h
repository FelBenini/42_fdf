/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:51:51 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/28 13:44:33 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"

typedef struct s_mlx_args
{
	void	*win;
	void	*mlx;
}	t_mlx_args;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img_data;

typedef struct s_3dpoint
{
	int	x;
	int	y;
	int	z;
}	t_3dpoint;

typedef struct s_2dpoint
{
	int	x;
	int	y;
}	t_2dpoint;

typedef struct s_bresenham
{
	int	delta_x;
	int	delta_y;
	int	step_x;
	int	step_y;
	int	error;
	int	swapped;
}	t_bresenham;

typedef struct s_environment
{
	t_img_data	img;
	t_mlx_args	mlx;
}	t_environment;

void			draw_pixel(t_img_data *data, int x, int y, int color);
void			draw_line(t_img_data *data, t_2dpoint *from,
					t_2dpoint *to, int start);

t_2dpoint		*new_2dpoint(int x, int y);
t_3dpoint		*new_3dpoint(int x, int y, int z);
t_2dpoint		*isometric_projection(t_3dpoint *point3d, double scale);

int				close_window(void *params);
int				handle_keymaps(int keycode, void *params);

t_3dpoint		***parse_map(char *filename);

t_environment	*init_environment(void);

#endif
