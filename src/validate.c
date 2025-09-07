/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 14:58:13 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/07 15:04:25 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	close_and_return(int fd, int return_value)
{
	close(fd);
	return (return_value);
}

int	validate_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR);
	if (fd < 0)
		return (0);
	return (close_and_return(fd, 1));
}
