/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:05:33 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/06 20:25:19 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	get_component(int value, int shift)
{
	return ((value >> shift) & 0xFF);
}

int	interpolate_color(int color1, int color2, double t)
{
	int		r;
	int		g;
	int		b;

	r = get_component(color1, 16) + t
		* (get_component(color2, 16) - get_component(color1, 16));
	g = get_component(color1, 8) + t
		* (get_component(color2, 8) - get_component(color1, 8));
	b = get_component(color1, 0) + t
		* (get_component(color2, 0) - get_component(color1, 0));
	return ((r << 16) | (g << 8) | b);
}

unsigned int	get_terrain_color(int height, t_environment *env)
{
	double	t;
	int		color1;
	int		color2;

	color1 = env->colors[1];
	color2 = env->colors[2];
	if (env->highest_z != env->lowest_z)
		t = (double)(height - env->lowest_z)
			/ (env->highest_z - env->lowest_z);
	else
		t = 0.0;
	if (height < 0)
	{
		color1 = env->colors[0];
		color2 = env->colors[1];
	}
	t = ft_norm(t);
	return (interpolate_color(color1, color2, t));
}

unsigned int	get_color(int height)
{
	t_environment	*env;
	t_gradient_args	g;

	env = *get_env();
	return (get_terrain_color(height, env));
	g.start_rgb = env->colors[0];
	g.end_rgb = env->colors[1];
	if (env->highest_z != env->lowest_z)
		g.normalized_z_t = (double)(height - env->lowest_z)
			/ (env->highest_z - env->lowest_z);
	else
		g.normalized_z_t = 0.0;
	g.normalized_z_t = ft_norm(g.normalized_z_t);
	return (interpolate_color(g.start_rgb, g.end_rgb, g.normalized_z_t));
}
