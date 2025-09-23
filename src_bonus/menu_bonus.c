/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:44:49 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/18 19:56:13 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	fill_color(t_img_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y <= img->height)
	{
		x = 0;
		while (x <= img->width)
		{
			draw_pixel(img, x, y, 0x343434);
			x++;
		}
		y++;
	}
}

static void	put_str(int y, int x, int color, char *str)
{
	t_environment	*env;

	env = *get_env();
	mlx_string_put(env->mlx.mlx, env->mlx.win,
		x, y, color, str);
}

static void	put_banner(void)
{
	int	start;
	int	color;
	int	r;

	start = 32;
	color = 0xFFFFFF;
	r = 1700;
	put_str(start, r, color, "  .-.          ___    .-.");
	put_str(start + 12, r, color, " /    \\       (   )  /    \\ ");
	put_str(start + 24, r, color, " | .`. ;    .-.| |   | .`. ;  ");
	put_str(start + 36, r, color, " | |(___)  /   \\ |   | |(___) ");
	put_str(start + 48, r, color, " | |_     |  .-. |   | |_     ");
	put_str(start + 60, r, color, "(   __)   | |  | |  (   __)   ");
	put_str(start + 72, r, color, " | |      | |  | |   | |      ");
	put_str(start + 84, r, color, " | |      | |  | |   | |      ");
	put_str(start + 96, r, color, " | |      | '  | |   | |      ");
	put_str(start + 108, r, color, " | |      ' `-'  /   | |      ");
	put_str(start + 120, r, color, "(___)      `.__,'   (___)     ");
}

void	print_menu(t_environment *env)
{
	fill_color(&env->menu);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.win,
		env->menu.img, 1920 - env->menu.width, 0);
	put_banner();
	put_str(188, 1672, 0xFFFFFF, "_______________COLORS________________");
	put_str(212, 1678, 0xFFFFFF, "0. DEFAULT");
	put_str(232, 1678, 0xFFFFFF, "1. TERRAIN");
	put_str(212, 1798, 0xFFFFFF, "2. VOID");
	put_str(232, 1798, 0xFFFFFF, "3. LAND");
	put_str(300, 1672, 0xFFFFFF, "______________CONTROLS_______________");
	put_str(332, 1672, 0xFFFFFF, "ARROW KEYS:      ROTATE");
	put_str(362, 1672, 0xFFFFFF, "WASD:            MOVE MODEL");
	put_str(392, 1672, 0xFFFFFF, "V AND B KEYS:    APPLY WAVY EFFECT");
	put_str(422, 1672, 0xFFFFFF, "MOUSE SCROLL:    ZOOM IN AND OUT");
	put_str(452, 1672, 0xFFFFFF, "[ AND ] KEYS:    MODIFY HEIGHT");
}
