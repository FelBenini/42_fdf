# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenini- <your@mail.com>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 14:39:13 by fbenini-          #+#    #+#              #
#    Updated: 2025/08/27 12:52:31 by fbenini-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

CFLAGS = -Wextra -Wall -Werror -no-pie

MINILIB = ./minilibx/libmlx_Linux.a

MINILIB_DIR = ./minilibx

MINILIB_HDR = ./minilibx/mlx.h

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft

LIBFT_HDR = ./libft/libft.h

SRCS = ./src/main.c \
	   ./src/draw.c \
	   ./src/point.c \
	   ./src/mlx.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(MINILIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(MINILIB_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lXext -lX11 -lm -lz -lft

$(MINILIB):
	@$(MAKE) -C $(MINILIB_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

clean:
	rm -rf $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MINILIB_DIR)

fclean: clean
	rm -rf $(MINILIB)
	rm -rf $(LIBFT)
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all fclean clean re
