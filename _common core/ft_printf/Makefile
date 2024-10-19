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

SRCB = f/ft_putsign.c
OBJB = $(SRCB:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJB)
	ar rcs $(NAME) $(OBJ) $(OBJB) ft_printf.h

bonus: $(OBJ) $(OBJB)
	ar rcs $(NAME) $(OBJ) $(OBJB) ft_printf.h

clean:
	rm -f $(OBJ)
	rm -f $(OBJB)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: bonus clean
	gcc main.c $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@
