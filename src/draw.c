/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:50:26 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/26 17:01:38 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	init_bresenham(t_bresenham *bresenham,
						t_2dpoint *from, t_2dpoint *to)
{
	bresenham->delta_x = ft_abs(to->x - from->x);
	bresenham->delta_y = ft_abs(to->y - from->y);
	bresenham->step_x = 1;
	bresenham->step_y = 1;
	if (from->x >= to->x)
		bresenham->step_x = -1;
	if (from->y >= to->y)
		bresenham->step_y = -1;
	bresenham->slope = bresenham->delta_x - bresenham->delta_y;
}

void	draw_line(t_img_data *data, t_2dpoint *from, t_2dpoint *to)
{
	t_bresenham	b;
	int			x;
	int			y;

	init_bresenham(&b, from, to);
	x = from->x;
	y = from->y;
	while (1)
	{
		draw_pixel(data, x, y, 0x00FF0000);
		if (x == to->x && y == to->y)
			break ;
		if (2 * b.slope > b.delta_y * -1)
		{
			b.slope -= b.delta_y;
			x += b.step_x;
		}
		if (2 * b.slope < b.delta_x)
		{
			b.slope += b.delta_x;
			y += b.step_y;
		}
	}
}
