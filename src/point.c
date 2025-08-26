/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:06:17 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/26 14:07:36 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_2dpoint	*new_2dpoint(int x, int y)
{
	t_2dpoint	*res;

	res = (t_2dpoint *)malloc(sizeof(t_2dpoint));
	res->x = x;
	res->y = y;
	return (res);
}
