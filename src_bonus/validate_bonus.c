/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 14:58:13 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/07 19:14:38 by fbenini-         ###   ########.fr       */
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

static int	check_elem(char *elem, int line_num, int column_num)
{
	char	*after_comma;
	int		returned;

	returned = 1;
	after_comma = ft_strnstr(elem, ",", ft_strlen(elem));
	if (ft_atoi(elem) == 0 && elem[0] != '0' && ft_strncmp(elem, "-0", 2) != 0)
		returned = 0;
	if (after_comma && ft_strncmp(after_comma, ",0x", 3) != 0)
		returned = 0;
	if (!returned)
		ft_printf("❌ Element at line %d, column %d is invalid.\n",
			line_num, column_num);
	return (returned);
}

static int	check_for_elems(char *line, int line_num)
{
	char	**splitted;
	int		i;

	splitted = ft_split(line, ' ');
	i = 0;
	while (splitted[i] && splitted[i][0] != '\n')
	{
		if (!check_elem(splitted[i], line_num, i + 1))
		{
			clear_splitted(splitted);
			return (0);
		}
		i++;
	}
	clear_splitted(splitted);
	return (1);
}

static int	is_valid(int fd, t_list **head)
{
	int		initial_line;
	char	*line;
	int		i;
	int		returned_value;

	line = get_next_line(fd);
	returned_value = 1;
	initial_line = count_elemnum(line);
	if (initial_line <= 0)
		returned_value = 0;
	i = 1;
	while (line)
	{
		if (count_elemnum(line) != initial_line && returned_value)
		{
			ft_printf("❌ Invalid format: Map must be a rectangle.\n");
			returned_value = 0;
		}
		ft_lstadd_back(head, ft_lstnew(line));
		if (!check_for_elems(line, i) && returned_value)
			returned_value = 0;
		line = get_next_line(fd);
		i++;
	}
	return (returned_value);
}

t_list	*validate_input(char *filename)
{
	int		fd;
	t_list	*res;

	fd = open(filename, O_RDWR);
	ft_printf("💾 Validating map file...\n");
	res = 0;
	if (fd < 0)
	{
		ft_printf("❌ File or directory not found.\n");
		return (0);
	}
	if (!is_valid(fd, &res))
	{
		ft_lstclear(&res, free);
		ft_printf("❌ File passed as input is invalid, try another one.\n");
		close(fd);
		return (0);
	}
	ft_printf("✅ Map is valid.\n");
	close(fd);
	return (res);
}
