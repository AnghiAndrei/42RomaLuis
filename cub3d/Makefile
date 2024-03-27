# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/03/05 17:00:26 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME = cub3D
CFLAGS = -Wall -Wextra -Werror

SRC = ft_split.c ft_strlen.c ft_strncmp.c \
	  get_next_line.c get_next_line_utils.c \
	  main.c marshal.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

git: fclean
	@git add .
	@git commit -m "voglio mangiare il tuo pancreas"
	@git push

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

test: re
	rm -f $(OBJ)
	clear
	echo /$(NAME)
	-./$(NAME)
	echo
	echo /$(NAME) 1.cub 2.cub
	-./$(NAME) 1.cub 2.cub
	@rm -f $(NAME)

test2: re
	rm -f $(OBJ)
	clear
	echo valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARG)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARG)
	@echo Norminette error: 
	norminette | grep Error! | wc -l
	@echo
# @leaks -atExit -- ./$(NAME) > temp.txt
# cat temp.txt | grep "total leaked bytes."
# rm temp.txt	
	@rm -f $(NAME)

test3: re
	rm -f $(OBJ)
	clear
	echo ./$(NAME) $(ARG)
	./$(NAME) $(ARG)
	@rm -f $(NAME)

$(ARG) = 1.cub