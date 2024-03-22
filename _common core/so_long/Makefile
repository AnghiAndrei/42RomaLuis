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

NAME =   so_long
NAMEB =   so_long_bonus
CFLAGS = -Wall -Wextra -Werror

SRC = main.c search.c print_map.c \
	  move.c move1.c \
	  utilitis.c utilitis1.c  utilitis2.c \
	  marshal1.c marshal2.c marshal3.c \
	  ft_strjoin.c ft_strncmp.c ft_split.c ft_strlen.c ft_substr.c ft_putnbr.c ft_itoa.c \
	  get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJ)
	gcc -o $(NAMEB) $(OBJ)

git:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -f $(NAME)
	@rm -f .DS_Store
	@git add .
	@git commit -m "commit"
	@git push

%.o: %.c
	gcc $(CFLAGS) -Imlx -c $< -o $@

test: re
	rm -f $(OBJ)
	clear
	./so_long "./maps/0.ber"
	./so_long "./maps/1.ber"
	./so_long "./maps/2.ber"
	./so_long "./maps/3.ber"
	./so_long "./maps/4.ber"
	./so_long "./maps/5.ber"
	@rm -f $(NAME)
