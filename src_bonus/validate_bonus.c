/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 14:58:13 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/07 17:11:38 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	count_elemnum(char *line)
{
	char	**splitted;
	int		i;

	splitted = ft_split(line, ' ');
	i = 0;
	while (splitted[i])
		i++;
	clear_splitted(splitted);
	return (i);
}

static int	check_elem(char *elem)
{
	char	*after_comma;
	int		returned;

	returned = 1;
	after_comma = ft_strnstr(elem, ",", ft_strlen(elem));
	if (ft_atoi(elem) == 0 && elem[0] != '0' && ft_strncmp(elem, "-0", 2) != 0)
		returned = 0;
	if (after_comma && ft_strncmp(after_comma, ",0x", 3) != 0)
		returned = 0;
	return (returned);
}

static int	check_for_elems(char *line, t_list **head)
{
	char	**splitted;
	int		i;

	splitted = ft_split(line, ' ');
	free(line);
	i = 0;
	while (splitted[i] && splitted[i][0] != '\n')
	{
		if (!check_elem(splitted[i]))
		{
			clear_splitted(splitted);
			return (0);
		}
		i++;
	}
	ft_lstadd_back(head, ft_lstnew(splitted));
	return (1);
}

static int	is_valid(int fd, t_list **head)
{
	int		initial_line;
	char	*line;
	int		returned_value;

	line = get_next_line(fd);
	returned_value = 1;
	initial_line = count_elemnum(line);
	if (initial_line <= 0)
		returned_value = 0;
	while (line)
	{
		if (!check_for_elems(line, head) && returned_value)
			returned_value = 0;
		line = get_next_line(fd);
	}
	return (returned_value);
}

t_list	*validate_input(int fd)
{
	t_list	*res;

	res = 0;
	if (!is_valid(fd, &res))
	{
		ft_lstclear(&res, clear_splitted);
		close(fd);
		return (0);
	}
	close(fd);
	return (res);
}
