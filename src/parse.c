/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:53:49 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/27 15:31:53 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

static t_3dpoint	***convert_list_to_matrix(t_list *head)
{
	t_3dpoint		***res;
	unsigned int	lst_size;
	unsigned int	i;
	unsigned int	j;
	char			**content;

	lst_size = ft_lstsize(head);
	i = 0;
	res = (t_3dpoint ***)ft_calloc(lst_size, sizeof(t_3dpoint **));
	if (!res)
		return (NULL);
	while (head->next)
	{
		j = 0;
		content = ft_split((char *)head->content, ' ');
		while (content[j++]);
		res[i] = (t_3dpoint **)ft_calloc(j, sizeof(t_3dpoint *));
		j = 0;
		while (content[j])
		{
			res[i][j] = new_3dpoint(j, i, ft_atoi(content[j]));
			j++;
		}
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
	res = convert_list_to_matrix(head);
	ft_lstclear(&head, free);
	return (res);
}
