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

NAME =   philo
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

SRC = main.c utiliti.c msg.c \
	  config.c config2.c \
	  ft_atoi.c ft_lstadd_back.c
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
	@rm -f .DS_Store
	@cd ..
	@rm -f .DS_Store
	@git add .
	@git commit -m "commit"
	@git push

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

test: re
	rm -f $(OBJ)
	clear
	echo /$(NAME)
	-./$(NAME)
	echo
	echo ./$(NAME) 0 800 200 200
	-./$(NAME) 0 800 200 200
	echo
	echo ./$(NAME) 2 0 200 200
	-./$(NAME) 2 0 200 200
	echo
	echo ./$(NAME) 2 800 0 200
	-./$(NAME) 2 800 0 200
	echo
	echo ./$(NAME) 2 800 200 0
	-./$(NAME) 2 800 200 0
	echo
	echo ./$(NAME) 0 0 0 0
	-./$(NAME) 0 0 0 0
	echo
	echo ./$(NAME) 2 800 200 0
	-./$(NAME) 2 800 200 0
	echo
	echo ./$(NAME) 0 0 0 0 0
	-./$(NAME) 0 0 0 0 0
	@rm -f $(NAME)

test2: re
	rm -f $(OBJ)
	clear
	echo valgrind --leak-check=full ./$(NAME) $(ARGS)
	valgrind --leak-check=full ./$(NAME) $(ARGS)
	@echo Norminette error: 
	norminette | grep Error! | wc -l
	@echo
# @leaks -atExit -- ./$(NAME) $(ARGS) > temp.txt
# cat temp.txt | grep "total leaked bytes."
# rm temp.txt	
	@rm -f $(NAME)

test3: re
	rm -f $(OBJ)
	clear
	echo ./$(NAME) $(ARGS)
	./$(NAME) $(ARGS)	
	@rm -f $(NAME)

# ARGS = 200 800 200 200

ARGS = 1 800 200 200 #no eat, dies
# ARGS = 5 800 200 200 #no dies ever
# ARGS = 5 800 200 200 7 #no dies, but finish at eat 7
# ARGS = 4 410 200 200 #no dies ever
# ARGS = 4 310 200 100 #one philo dies

# ARGS = 2 800 200 200 #no dies ever
# ARGS = 2 800 200 200 7 #no dies, but finish at eat 7
# ARGS = 2 410 200 200 #no dies ever
# ARGS = 2 310 200 100 #uno philo dies
