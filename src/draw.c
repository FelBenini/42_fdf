/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:50:26 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/01 18:06:30 by fbenini-         ###   ########.fr       */
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
	int	temp;

	bresenham->delta_x = ft_abs(to->x - from->x);
	bresenham->delta_y = ft_abs(to->y - from->y);
	bresenham->step_x = -1;
	bresenham->step_y = -1;
	bresenham->swapped = 0;
	if (from->x < to->x)
		bresenham->step_x = 1;
	if (from->y < to->y)
		bresenham->step_y = 1;
	if (bresenham->delta_y > bresenham->delta_x)
	{
		temp = bresenham->delta_x;
		bresenham->delta_x = bresenham->delta_y;
		bresenham->delta_y = temp;
		bresenham->swapped = 1;
	}
	bresenham->error = bresenham->delta_x / 2;
	bresenham->total_steps = ft_gethigher(bresenham->delta_x,
										bresenham->delta_y);
}

void	draw_line(t_img_data *data, t_2dpoint *from, t_2dpoint *to, int start)
{
	t_bresenham	b;
	int			x;
	int			y;

	init_bresenham(&b, from, to);
	x = from->x;
	y = from->y;
	while (start <= b.delta_x)
	{
		draw_pixel(data, x, y, get_color(from->height, to->height, start, b.total_steps));
		b.error -= b.delta_y;
		if (b.error < 0)
		{
			b.error += b.delta_x;
			if (b.swapped)
				x += b.step_x;
			else
				y += b.step_y;
		}
		if (b.swapped)
			y += b.step_y;
		else
			x += b.step_x;
		start++;
	}
}
