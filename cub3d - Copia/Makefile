# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/04/16 11:26:37 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
ARG = maps/1.cub

MINILIBX_PATH = ./mlx
MINILIBX = $(MINILIBX_PATH)/libmlx.a

SRC = ft_split.c ft_strlen.c ft_strncmp.c ft_substr.c ft_strjoin.c \
	  get_next_line.c get_next_line_utils.c \
	  main.c marshal.c controlls.c print.c \
	  utilitis.c utilitis1.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(MINILIBX)
	gcc $(OBJ) $(CFLAGS) $(MINILIBX) mlx/libmlx.a -L./mlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

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
	gcc $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(MINILIBX):
	chmod 777 mlx/configure
	make -C $(MINILIBX_PATH)

test: re
	rm -f $(OBJ)
	clear
	echo /$(NAME)
	-./$(NAME)
	echo
	echo /$(NAME) maps/1.cub maps/2.cub
	-./$(NAME) maps/1.cub maps/2.cub
	echo
	echo /$(NAME) maps/no_exist.cub
	-./$(NAME) maps/no_exist.cub
	echo
	echo /$(NAME) maps/1.angly
	-./$(NAME) maps/1.angly
	echo
	echo /$(NAME) maps/error1.cub
	-./$(NAME) maps/error1.cub
	echo
	echo /$(NAME) maps/error2.cub
	-./$(NAME) maps/error2.cub
	echo
	echo /$(NAME) maps/error3.cub
	-./$(NAME) maps/error3.cub
	echo
	echo /$(NAME) maps/error4.cub
	-./$(NAME) maps/error4.cub
	echo
	echo /$(NAME) maps/error5.cub
	-./$(NAME) maps/error5.cub
	@rm -f $(NAME)

test2: re
	rm -f $(OBJ)
	clear
	echo valgrind ./$(NAME) $(ARG)
	valgrind --leak-check=full --track-origins=yes ./$(NAME) $(ARG)
#valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARG)
#valgrind --leak-check=full ./$(NAME) $(ARG)
	@echo Norminette error: 
	norminette $(SRC) cub3d.h | grep Error! | wc -l
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

norma: 
	norminette $(SRC) cub3d.h