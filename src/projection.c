/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:00:59 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/27 18:04:44 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_2dpoint	*isometric_projection(t_3dpoint *point3d, double scale)
{
	t_2dpoint	*res;
	
	res = (t_2dpoint *)malloc(sizeof(t_2dpoint));
	res->x = (int)((point3d->x - point3d->z) * scale);
	res->y = (int)((point3d->x + point3d->z - 2 * point3d->y) * 0.5 * scale);
	return (res);
}
