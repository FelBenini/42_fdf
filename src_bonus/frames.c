/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:49:24 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/02 17:14:14 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <fcntl.h>
#include <sys/time.h>

static t_list	*parse_single_frame(char *directory_name, char *iter)
{
	char	*file_name;
	char	*final_name;
	t_list	*file_content;
	t_list	*res;
	int		fd;

	file_name = ft_strjoin(directory_name, iter);
	free(iter);
	final_name = ft_strjoin(file_name, ".fdf");
	free(file_name);
	fd = open(final_name, O_RDWR);
	if (fd < 0)
	{
		free(final_name);
		return (NULL);
	}
	file_content = validate_input(fd);
	if (!file_content)
	{
		free(final_name);
		return (NULL);
	}
	free(final_name);
	res = ft_lstnew(parse_map(&file_content));
	return (res);
}

static t_list	*loop_through_files(char *directory_name)
{
	char	*dir_name_ending_slash;
	int		i;
	t_list	*frame;
	t_list	*head;

	dir_name_ending_slash = ft_strjoin(directory_name, "/");
	i = 0;
	frame = parse_single_frame(dir_name_ending_slash, ft_itoa(i++));
	if (!frame && i == 0)
	{
		ft_lstclear(&head, clear_matrix);
		return (NULL);
	}
	head = frame;
	ft_printf("\n");
	while (frame)
	{
		frame = parse_single_frame(dir_name_ending_slash, ft_itoa(i++));
		ft_printf("✅ Parsed %d frames\r", i);
		ft_lstadd_back(&head, frame);
	}
	ft_printf("\n");
	free(dir_name_ending_slash);
	return (head);
}

t_list	*parse_frames(char *directory_name)
{
	t_list	*head;
	t_list	*frame;
	int		file;
	t_list	*file_content;

	file = open(directory_name, O_RDWR);
	if (file >= 0)
	{
		ft_printf("Validanting map file...\n");
		file_content = validate_input(file);
		if (!file_content)
		{
			ft_printf("❌ ERROR: Map is Invalid.\n");
			ft_lstclear(&file_content, free);
			return (NULL);
		}
		frame = ft_lstnew(parse_map(&file_content));
		ft_lstclear(&file_content, free);
		head = frame;
		ft_printf("👍 Map is valid!\n");
		return (head);
	}
	head = loop_through_files(directory_name);
	return (head);
}

int loop_through_frames(t_environment *env)
{
	static t_list			*current_frame = NULL;
	static struct timeval	last_time = {0, 0};
	struct timeval			current_time;
	long long				time_diff;

	gettimeofday(&current_time, NULL);
	time_diff = (current_time.tv_sec - last_time.tv_sec)
		* 1000000 + (current_time.tv_usec - last_time.tv_usec);
	if (time_diff >= 41667)
	{
		if (!env->frames)
			return (0);
		if (!current_frame)
			current_frame = env->frames;
		env->map = current_frame->content;
		print_matrix(env);
		if (current_frame->next)
			current_frame = current_frame->next;
		else
			current_frame = env->frames;
		last_time = current_time;
	}
	return (0);
}
