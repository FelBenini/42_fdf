/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:53:49 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/07 15:14:31 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_3dpoint	***parse_map(char *filename)
{
	t_list		*head;
	int			file;
	char		*line;
	t_3dpoint	***res;

	file = open(filename, O_RDWR);
	line = get_next_line(file);
	head = ft_lstnew(line);
	while (line)
	{
		line = get_next_line(file);
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	res = convert_list_to_matrix(head, ft_lstsize(head));
	ft_lstclear(&head, free);
	return (res);
}
