/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:16:50 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/07 16:17:29 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	initialize_camera(t_environment *env)
{
	env->camera.x_cos = cos(0.0);
	env->camera.x_sin = sin(0.0);
	env->camera.z_cos = cos(0.0);
	env->camera.z_sin = sin(0.0);
	env->camera.y_cos = cos(0.0);
	env->camera.y_sin = sin(0.0);
	env->camera.x_rotation = 0.0;
	env->camera.y_rotation = 0.0;
	env->camera.z_rotation = 0.0;
	env->camera.offset_x = 0;
	env->camera.offset_y = 0;
	env->camera.projection = PARALLEL;
}
