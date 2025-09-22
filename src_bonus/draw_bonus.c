/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:50:26 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/06 20:48:42 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	draw_pixel(t_img_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	init_bresenham(t_bresenham *bresenham,
						t_2dpoint from, t_2dpoint to)
{
	int	temp;

	bresenham->delta_x = ft_abs(to.x - from.x);
	bresenham->delta_y = ft_abs(to.y - from.y);
	bresenham->step_x = -1;
	bresenham->step_y = -1;
	bresenham->swapped = 0;
	if (from.x < to.x)
		bresenham->step_x = 1;
	if (from.y < to.y)
		bresenham->step_y = 1;
	if (bresenham->delta_y > bresenham->delta_x)
	{
		temp = bresenham->delta_x;
		bresenham->delta_x = bresenham->delta_y;
		bresenham->delta_y = temp;
		bresenham->swapped = 1;
	}
	bresenham->error = bresenham->delta_x / 2;
	bresenham->x = from.x;
	bresenham->y = from.y;
	bresenham->total_steps = ft_gethigher(bresenham->delta_x,
			bresenham->delta_y);
}

void	draw_line(t_img_data *data, t_2dpoint from, t_2dpoint to, int start)
{
	t_bresenham	b;
	double		t;

	init_bresenham(&b, from, to);
	while (start <= b.total_steps)
	{
		t = (double)start / b.total_steps;
		draw_pixel(data, b.x, b.y,
			interpolate_color(from.color, to.color, t));
		b.error -= b.delta_y;
		if (b.error < 0)
		{
			b.error += b.delta_x;
			if (b.swapped)
				b.x += b.step_x;
			else
				b.y += b.step_y;
		}
		if (b.swapped)
			b.y += b.step_y;
		else
			b.x += b.step_x;
		start++;
	}
}
