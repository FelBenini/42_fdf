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
	while (head->next)
	{
		j = 0;
		content = ft_split((char *)head->content, ' ');
		while (content[j])
			j++;
		res[i] = (t_3dpoint **)ft_calloc(j + 1, sizeof(t_3dpoint *));
		j = 0;
		while (content[j++])
			res[i][j - 1] = new_3dpoint(j - 1, i, ft_atoi(content[j - 1]),
					ft_strnstr(content[j - 1], ",0x", 30));
		clear_splitted(content);
		head = head->next;
		i++;
	}
	return (res);
}

static	void	get_dimensions(t_3dpoint ***matrix)
{
	int				x;
	int				y;
	t_environment	*env;

	y = 0;
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

t_3dpoint	**convert_matrix_to_arr(t_3dpoint ***matrix)
{
	t_3dpoint	**res;
	int			i;
	int			x;
	int			y;
	int			total_points;

	total_points = 0;
	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
		{
			total_points++;
			x++;
		}
		y++;
	}
	res = ft_calloc(total_points + 1, sizeof(t_3dpoint *));
	i = 0;
	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
		{
			res[i] = matrix[y][x];
			if (matrix[y][x + 1])
				res[i]->next = matrix[y][x + 1];
			if (matrix[y + 1] && matrix[y + 1][x])
				res[i]->below = matrix[y + 1][x];
			x++;
			i++;
		}
		free(matrix[y]);
		y++;
	}
	free(matrix);
	return (res);
}

t_3dpoint	**parse_map(char *filename)
{
	t_list		*head;
	int			file;
	char		*line;
	t_3dpoint	***matrix;
	t_3dpoint	**res;

	file = open(filename, O_RDWR);
	line = get_next_line(file);
	head = ft_lstnew(line);
	while (line)
	{
		line = get_next_line(file);
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	matrix = convert_list_to_matrix(head, ft_lstsize(head));
	get_dimensions(matrix);
	ft_lstclear(&head, free);
	res = convert_matrix_to_arr(matrix);
	return (res);
}
