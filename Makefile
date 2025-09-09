# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenini- <your@mail.com>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 14:39:13 by fbenini-          #+#    #+#              #
#    Updated: 2025/09/07 15:03:44 by fbenini-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc

CFLAGS = -O3 -Wextra -Wall -Werror

MINILIB = ./minilibx/libmlx_Linux.a

MINILIB_DIR = ./minilibx

MINILIB_HDR = ./minilibx/mlx.h

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft

LIBFT_HDR = ./libft/libft.h

HDR = ./src/fdf.h

SRCS = ./src/main.c \
	   ./src/draw.c \
	   ./src/point.c \
	   ./src/parse.c \
	   ./src/mlx.c \
	   ./src/projection.c \
	   ./src/initializers.c \
	   ./src/cleaners.c \
	   ./src/colors.c \
	   ./src/validate.c

HDR_BONUS = ./src_bonus/fdf_bonus.h

SRCS_BONUS = ./src_bonus/main_bonus.c \
	   ./src_bonus/draw_bonus.c \
	   ./src_bonus/point_bonus.c \
	   ./src_bonus/parse_bonus.c \
	   ./src_bonus/mlx_bonus.c \
	   ./src_bonus/projection_bonus.c \
	   ./src_bonus/initializers_bonus.c \
	   ./src_bonus/cleaners_bonus.c \
	   ./src_bonus/colors_bonus.c \
	   ./src_bonus/validate_bonus.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(SRCS_BONUS:.c=.o)

$(OBJS): %.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_BONUS): %.o: %.c $(HDR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(MINILIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(MINILIB_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lXext -lX11 -lm -lz -lft

$(MINILIB):
	@$(MAKE) -C $(MINILIB_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

bonus: $(BONUS_OBJS) $(MINILIB) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME) -L$(MINILIB_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lXext -lX11 -lm -lz -lft

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MINILIB_DIR)

fclean: clean
	rm -rf $(MINILIB)
	rm -rf $(LIBFT)
	rm -rf $(NAME)

re: fclean $(NAME)

re-bonus: fclean bonus

.PHONY: all fclean clean re bonus re-bonus
