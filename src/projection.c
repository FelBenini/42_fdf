/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:00:59 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/28 13:43:38 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_2dpoint	*isometric_projection(t_3dpoint *point3d, double scale)
{
	t_2dpoint	*res;
	double		projected_x;
	double		projected_y;

	res = (t_2dpoint *)malloc(sizeof(t_2dpoint));
	if (res == NULL)
		return (NULL);
	projected_x = (point3d->x - point3d->y) * 0.866;
	projected_y = (point3d->x + 2 * point3d->y + -point3d->z) * 0.5;
	res->x = (int)(projected_x * scale);
	res->y = (int)(projected_y * scale);
	res->x += 300;
	res->y += 200;
	return (res);
}
