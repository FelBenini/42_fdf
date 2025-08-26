/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:53:49 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/24 10:00:16 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3dpoint	***parse_map(char *filename)
{
	t_list	*head;
	int		file;
	char	*line;

	file = open(filename, 1);
	line = get_next_line(file);
	head = ft_lstnew(line);
	while (line)
	{
		line = get_next_line(file);
		ft_lstadd_front(&head, ft_lstnew(line));
	}
}
