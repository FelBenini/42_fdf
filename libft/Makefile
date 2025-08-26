# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenini- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 19:14:42 by fbenini-          #+#    #+#              #
#    Updated: 2025/07/22 13:31:18 by fbenini-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

SRCS =	ft_atoi.c \
		ft_isalnum.c \
		ft_isdigit.c \
		ft_memcpy.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_strdup.c \
		ft_strlcat.c \
		ft_strmapi.c \
		ft_strrchr.c \
		ft_tolower.c \
		ft_bzero.c \
		ft_isalpha.c \
		ft_isprint.c \
		ft_memchr.c \
		ft_memmove.c \
		ft_putendl_fd.c \
		ft_split.c \
		ft_striteri.c \
		ft_strlcpy.c \
		ft_strncmp.c \
		ft_strtrim.c \
		ft_toupper.c \
		ft_calloc.c \
		ft_isascii.c \
		ft_itoa.c \
		ft_memcmp.c \
		ft_memset.c \
		ft_putnbr_fd.c \
		ft_strchr.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strnstr.c \
		ft_substr.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstlast.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_parse_special.c \
		ft_printchar.c \
		ft_printf.c \
		ft_printhex.c \
		ft_printnbr.c \
		ft_printptr.c \
		ft_printstr.c \
		ft_printunsigned.c \
		ft_hex_util.c \
		ft_strrev.c \
		ft_intlen.c \
		ft_utoa.c \
		get_next_line.c

HDRS = libft.h

PRINTF_HDRS = ft_printf.h

OBJS = $(SRCS:.c=.o)

LST_OBJS = $(LST_SCRS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I.$(HDRSi) -I.$(PRINTF_HDRS) -c $^ -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
