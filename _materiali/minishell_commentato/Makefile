# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/04/05 14:49:54 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g

SRC = ft_atoi.c ft_strncmp.c ft_lstadd_back.c ft_isdigit.c ft_strjoin.c ft_itoa.c ft_strlen.c ft_split.c ft_substr.c \
	  get_args.c get_args_utilis.c get_args_expander.c get_args_redirect.c \
	  main.c u_input.c split_cmd.c marshal.c \
	  get_next_line.c get_next_line_utils.c \
	  builtins1.c builtins2.c builtins3.c \
	  utilitis.c utilitis1.c utilitis2.c \
	  executor.c executor1.c \
	  builtins_utilitis.c \
	  here_doc.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) -lreadline

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

git: fclean
	@rm -f .DS_Store
	@cd ..
	@rm -f .DS_Store
	@git add .
	@git commit -m "commit"
	@git push

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ -lreadline

test: re
	rm -f $(OBJ)
	clear
	echo /$(NAME) input
	-./$(NAME) input
	echo
	echo /$(NAME) input1 input2
	-./$(NAME) input1 input2
	@rm -f $(NAME)

test2: re
	rm -f $(OBJ)
	clear
	echo valgrind ./$(NAME)
	-valgrind --leak-check=full --track-origins=yes ./$(NAME)
#-valgrind --leak-check=full --track-origins=yes ./$(NAME)
#-valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

#echo Norminette error: 
#norminette | grep Error! | wc -l
#echo

# @leaks -atExit -- ./$(NAME) > temp.txt
# cat temp.txt | grep "total leaked bytes."
# rm temp.txt	
	@rm -f $(NAME)

test3: re
	rm -f $(OBJ)
	clear
	echo ./$(NAME)
	./$(NAME)
	@rm -f $(NAME)
