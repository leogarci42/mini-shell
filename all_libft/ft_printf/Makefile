# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 13:03:33 by leogarci          #+#    #+#              #
#    Updated: 2024/12/26 15:21:00 by leogarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_printf.c \
		./utils/ft_printf_char.c \
		./utils/ft_printf_int.c \
		./utils/ft_printf_modulo_and_flags.c \
		./utils/ft_utils_bis.c \
		./utils/ft_printf_args.c \
		./utils/ft_utils.c \
		./utils/ft_printf_flag_handling.c
OBJ = $(SRCS:.c=.o)
NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $^

%.o: %.c ft_printf.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
