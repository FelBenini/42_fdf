/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:51:51 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/15 20:01:35 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <math.h>

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
	int					x;
	int					y;
	int					z;
	int					color;
	int					has_color;
	struct s_3dpoint	*next;
	struct s_3dpoint	*below;
}	t_3dpoint;

typedef struct s_2dpoint
{
	int	x;
	int	y;
	int	height;
	int	color;
}	t_2dpoint;

typedef struct s_bresenham
{
	int	x;
	int	y;
	int	delta_x;
	int	delta_y;
	int	step_x;
	int	step_y;
	int	error;
	int	swapped;
	int	total_steps;
}	t_bresenham;

typedef struct s_camera
{
	double	x_cos;
	double	y_cos;
	double	z_cos;
	double	x_sin;
	double	y_sin;
	double	z_sin;
	double	y_rotation;
	double	x_rotation;
	double	z_rotation;
}	t_camera;

typedef struct s_keys
{
	int	scroll_pressed;
	int	last_x;
	int	last_y;
}	t_keys;

typedef struct s_environment
{
	t_img_data		img;
	t_mlx_args		mlx;
	t_camera		camera;
	t_3dpoint		**map;
	t_keys			keys;
	int				width;
	int				height;
	int				highest_x;
	int				lowest_x;
	int				highest_y;
	int				lowest_y;
	int				highest_z;
	int				lowest_z;
	double			scale;
	int				offset_x;
	int				offset_y;
	double			z_factor;
	unsigned int	colors[3];
}	t_environment;

typedef struct s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_rgb;

typedef struct s_gradient_args
{
	double			normalized_z_t;
	double			segment_t;
	t_rgb			start_rgb;
	t_rgb			end_rgb;
}	t_gradient_args;

void			draw_pixel(t_img_data *data, int x, int y, unsigned int color);
void			draw_line(t_img_data *data, t_2dpoint from,
					t_2dpoint to, int start);

t_2dpoint		*new_2dpoint(int x, int y, int z);
t_3dpoint		*new_3dpoint(int x, int y, int z, char *color);
t_2dpoint		isometric_projection(t_3dpoint *point3d);
void			normalize_map(t_environment *env);

int				close_window(void *params);
int				handle_keymaps(int keycode, void *params);

t_3dpoint		**parse_map(char *filename);

t_environment	**get_env(void);
t_environment	*init_environment(char *filename);
void			get_highest_projections(t_3dpoint *point_3d);

void			clean_env(t_environment *env);
void			clear_splitted(char **splitted);

unsigned int	get_color(int height);
t_rgb			create_rgba(unsigned int color);
unsigned int	interpolate_rgba(t_rgb start_comp, t_rgb end_comp,
					double t);
t_rgb			create_rgba(unsigned int color);
void			set_background(t_img_data *img);

int				validate_input(char *filename);

void			print_matrix(t_environment *env);

int				rotate(int keycode, void *params);
void			change_scale(int value, t_environment *env);

int				mouse_press(int key, int x, int y, void *param);
int				mouse_drop(int key, int x, int y, void *param);

#endif
