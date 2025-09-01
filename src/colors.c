/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:05:33 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/01 18:53:45 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	create_hex_color(t_rgba	rgba)
{
	return ((rgba.a << 24) | (rgba.r << 16) | (rgba.g << 8) | rgba.b);
}

static unsigned char	get_component(unsigned int color, int shift)
{
	return (unsigned char)((color >> shift) & 0xFF);
}

static t_rgba	interpolate_rgba(t_rgba start_comp, t_rgba end_comp, double t)
{
	t_rgba	res;

	res.r = (unsigned char)(start_comp.r + t * (end_comp.r - start_comp.r));
	res.g = (unsigned char)(start_comp.g + t * (end_comp.g - start_comp.g));
	res.b = (unsigned char)(start_comp.b+ t * (end_comp.b - start_comp.b));
	res.a = (unsigned char)(start_comp.a + t * (end_comp.a - start_comp.a));
	return (res);
}

static t_rgba	create_rgba(unsigned int color)
{
	t_rgba	res;

	res.a = get_component(color, 24);
	res.r = get_component(color, 16);
	res.g = get_component(color, 8);
	res.b = get_component(color, 0);
	return (res);
}

unsigned int get_color(int from_z, int to_z, int current_step, int total_steps)
{
    t_environment	*env;
    int				current_z_value;
    double			normalized_z_t;
    double			segment_t;
    double			seg1_end = 0.33333;
    double			seg2_end = 0.66666;
	t_rgba			start_rgb;
	t_rgba			end_rgb;
	t_rgba			interpolated_rgba;
	unsigned int	color1 = 0x0000FF;
	unsigned int	color2 = 0x0000FF;
	unsigned int	color3 = 0xFFFF00;
	unsigned int	color4 = 0xFF0000;

	env = *get_env();
	if (total_steps == 0)
		current_z_value = from_z;
	else
		current_z_value = from_z + (int)(((double)current_step / total_steps) * (to_z - from_z));
	if (env->highest_z == env->lowest_z)
		normalized_z_t = 0.5;
	else
		normalized_z_t = (double)(current_z_value - env->lowest_z) / (env->highest_z - env->lowest_z);
    if (normalized_z_t < 0.0)
		normalized_z_t = 0.0;
    if (normalized_z_t > 1.0)
		normalized_z_t = 1.0;
    if (normalized_z_t <= seg1_end)
    {
		start_rgb = create_rgba(color1);
		end_rgb = create_rgba(color2);
        segment_t = normalized_z_t / seg1_end;
    }
    else if (normalized_z_t <= seg2_end)
    {
		start_rgb = create_rgba(color2);
		end_rgb = create_rgba(color3);
        segment_t = (normalized_z_t - seg1_end) / (seg2_end - seg1_end);
    }
    else
    {
		start_rgb = create_rgba(color3);
		end_rgb = create_rgba(color4);
        segment_t = (normalized_z_t - seg2_end) / (1.0 - seg2_end);
    }
    if (segment_t < 0.0) segment_t = 0.0;
    if (segment_t > 1.0) segment_t = 1.0;
	interpolated_rgba = interpolate_rgba(start_rgb, end_rgb, segment_t);
    return (create_hex_color(interpolated_rgba));
}
