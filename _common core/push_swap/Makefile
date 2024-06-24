# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/06/24 11:27:29 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME =   push_swap
CFLAGS = -Wall -Wextra -Werror

MAINP = main.c
OBJP = $(MAINP:.c=.o)

MAINC = checker.c
OBJC = $(MAINC:.c=.o)

SRC = utilitis.c marshal.c operations.c \
	  sort.c sort1.c \
	  get_next_line.c get_next_line_utils.c \
	  ft_split.c ft_substr.c ft_strlen.c ft_atoi.c ft_strncmp.c ft_putstr.c \
	  ft_lstadd_back.c ft_lstlen.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJP)
	gcc -o $(NAME) $(OBJ) $(OBJP)

bonus: $(OBJ) $(OBJC)
	gcc -o checker $(OBJ) $(OBJC)

clean:
	rm -f $(OBJ)
	rm -f $(OBJC)
	rm -f $(OBJP)
	rm -f $(OBJC)

fclean: clean
	rm -f $(NAME)
	rm -f checker

re: fclean all

git: fclean
	@rm -f .DS_Store
	@git add .
	@git commit -m "commit"
	@git push

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

test: re bonus
	rm -f $(OBJ)
	rm -f $(OBJC)
	rm -f $(OBJP)
	rm -f $(OBJC)
	clear
	echo ./$(NAME)
	-./$(NAME)
	echo
	echo ./$(NAME) '""'
	-./$(NAME) ""
	echo
	echo ./$(NAME) "''"
	-./$(NAME) ''
	echo
	echo ./$(NAME) '"   "'
	-./$(NAME) "   "
	echo
	echo ./$(NAME) 42 42
	-./$(NAME) 42 42
	echo
	echo ./$(NAME) Voglio mangiare il tuo pancreas
	-./$(NAME) Voglio mangiare il tuo pancreas
	echo
	echo ./$(NAME) '"Voglio mangiare il tuo pancreas"'
	-./$(NAME) "Voglio mangiare il tuo pancreas"
	echo
	echo ./$(NAME) '"Voglio mangiare il tuo pancreas"' 42
	-./$(NAME) "Voglio mangiare il tuo pancreas" 42
	echo
	echo ./$(NAME) '"42"' Voglio mangiare il tuo pancreas
	-./$(NAME) "42" Voglio mangiare il tuo pancreas
	echo
	echo ./$(NAME) '"++42"'
	-./$(NAME) "++42"
	echo
	echo ./$(NAME) '"--42"'
	-./$(NAME) "--42"
	echo
	echo ./$(NAME) 43 '"42 7 18 12"' 23
	-./$(NAME) 43 "42 7 18 12" 23
	echo
	echo ./$(NAME) \"\'\'\"
	-./$(NAME) "''"
	clear
	echo ./$(NAME) $(ARGS)
	./$(NAME) $(ARGS)
	@echo
	@echo "N. mosse: "
	@./$(NAME) $(ARGS) | wc -l
	@echo
	@echo "Corretto: "
	@./$(NAME) $(ARGS) | ./checker $(ARGS)
	@echo
	@echo Norminette error: 
	norminette | grep Error! | wc -l
	@echo
	@echo "Leaks: $(NAME)"
	@leaks -atExit -- ./$(NAME) $(ARGS) > temp.txt
	cat temp.txt | grep "total leaked bytes."
	echo 
	@echo "Leaks: checker"
	@leaks -atExit -- ./checker > temp.txt
	cat temp.txt | grep "total leaked bytes."
	rm temp.txt
	@rm -f $(NAME)
	@rm -f checker

ARGS=$$(shuf -i 1-200 -n 100 | tr "\n" " ")
