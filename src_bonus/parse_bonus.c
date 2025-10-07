/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:53:49 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/15 19:47:35 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static t_3dpoint	***convert_list_to_matrix(t_list *head,
											unsigned int lst_size)
{
	t_3dpoint		***res;
	unsigned int	i;
	unsigned int	j;
	char			**content;

	i = 0;
	res = (t_3dpoint ***)ft_calloc(lst_size + 1, sizeof(t_3dpoint **));
	if (!res)
		return (NULL);
	while (head)
	{
		j = 0;
		content = (char **)head->content;
		while (content[j])
			j++;
		res[i] = (t_3dpoint **)ft_calloc(j + 1, sizeof(t_3dpoint *));
		j = 0;
		while (content[j++])
			res[i][j - 1] = new_3dpoint(j - 1, i, ft_atoi(content[j - 1]),
					ft_strnstr(content[j - 1], ",0x", 30));
		head = head->next;
		i++;
	}
	return (res);
}

void	get_dimensions(t_3dpoint ***matrix)
{
	int				x;
	int				y;
	t_environment	*env;

	y = 0;
	x = 0;
	env = *get_env();
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
			x++;
		y++;
	}
	env->width = x;
	env->height = y;
}

t_3dpoint	***parse_map(t_list **head)
{
	t_3dpoint	***res;

	res = convert_list_to_matrix(*head, ft_lstsize(*head));
	ft_lstclear(head, clear_splitted);
	return (res);
}
