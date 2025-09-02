/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:05:33 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/02 20:33:05 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned char	get_component(unsigned int color, int shift)
{
	return ((unsigned char)((color >> shift) & 0xFF));
}

static unsigned int	interpolate_rgba(t_rgba start_comp, t_rgba end_comp,
									double t)
{
	t_rgba	res;

	res.r = (unsigned char)(start_comp.r + t
			* (end_comp.r - start_comp.r) + 0.5);
	res.g = (unsigned char)(start_comp.g + t
			* (end_comp.g - start_comp.g) + 0.5);
	res.b = (unsigned char)(start_comp.b + t
			* (end_comp.b - start_comp.b) + 0.5);
	res.a = (unsigned char)(start_comp.a + t
			* (end_comp.a - start_comp.a) + 0.5);
	return ((res.a << 24) | (res.r << 16) | (res.g << 8) | res.b);
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

t_gradient_args	init_gradient(int from_z, int to_z,
							int current_step, int total_steps)
{
	t_environment	*env;
	t_gradient_args	res;

	env = *get_env();
	if (total_steps == 0)
		res.normalized_z_t = from_z;
	else
		res.normalized_z_t = from_z + (int)(((double)current_step
					/ total_steps) * (to_z - from_z));
	if (env->highest_z == env->lowest_z)
		res.normalized_z_t = 0.5;
	else
		res.normalized_z_t = (double)(res.normalized_z_t - env->lowest_z)
			/ (env->highest_z - env->lowest_z);
	res.normalized_z_t = ft_norm(res.normalized_z_t);
	return (res);
}

unsigned int	get_color(int from_z, int to_z,
							int current_step, int total_steps)
{
	t_environment	*env;
	t_gradient_args	g;

	env = *get_env();
	g = init_gradient(from_z, to_z, current_step, total_steps);
	if (g.normalized_z_t <= 0.5)
	{
		g.start_rgb = create_rgba(env->colors[0]);
		g.end_rgb = create_rgba(env->colors[1]);
		g.segment_t = g.normalized_z_t / 0.5;
	}
	else
	{
		g.start_rgb = create_rgba(env->colors[1]);
		g.end_rgb = create_rgba(env->colors[2]);
		g.segment_t = (g.normalized_z_t - 0.5) / 0.5;
	}
	g.segment_t = ft_norm(g.segment_t);
	return (interpolate_rgba(g.start_rgb, g.end_rgb, g.segment_t));
}
