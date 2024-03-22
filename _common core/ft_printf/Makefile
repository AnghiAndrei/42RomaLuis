# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/01/18 17:55:23 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =   libftprintf.a
CFLAGS = -Wall -Wextra -Werror

SRC = ft_printf.c \
	  t/ft_strlen.c t/ft_len_int.c \
	  f/ft_putchar.c f/ft_puthex.c f/ft_putnbr.c  f/ft_putstr.c f/ft_putvoid.c f/ft_putnbrf.c f/ft_putnbru.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ) ft_printf.h

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME) clean
	gcc main.c $(NAME)
	rm -f $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@
