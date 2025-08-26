/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:44:47 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/11 17:51:56 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

static char	*get_current_line(char *str)
{
	int		len;
	int		i;
	char	*line;

	len = 0;
	i = 0;
	if (!str || !str[i])
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	line = (char *)ft_calloc(len + 2, sizeof(char));
	if (!line)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i++] = '\0';
	return (line);
}

static char	*get_remainder(char *src)
{
	char	*res;
	char	*remainder;
	int		i;

	if (!src)
		return (NULL);
	remainder = ft_strchr(src, '\n');
	if (remainder)
		remainder++;
	else
	{
		free(src);
		return (NULL);
	}
	i = 0;
	res = (char *)malloc((ft_strlen(remainder) + 1) * sizeof(char));
	while (remainder[i])
	{
		res[i] = remainder[i];
		i++;
	}
	res[i] = '\0';
	free(src);
	return (res);
}

static char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		bytes_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!res)
		res = ft_calloc(1, 1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(res);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		res = join_and_free(res, buffer);
		if (ft_strchr(res, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	current_line = get_current_line(buffer[fd]);
	buffer[fd] = get_remainder(buffer[fd]);
	return (current_line);
}
