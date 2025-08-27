/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:51:51 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/27 12:52:07 by fbenini-         ###   ########.fr       */
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
	int	slope;
}	t_bresenham;

void		draw_pixel(t_img_data *data, int x, int y, int color);
void		draw_line(t_img_data *data, t_2dpoint *from, t_2dpoint *to);

t_2dpoint	*new_2dpoint(int x, int y);

int			close_window(void *params);

#endif
