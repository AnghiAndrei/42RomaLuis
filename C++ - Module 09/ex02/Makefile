# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/06/14 15:42:10 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRC = main.cpp PmergeMe.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.cpp
	c++ $(CFLAGS) -c $< -o $@

ARG1=$$(shuf -i 1-9 -n 1 | tr "\n" " ")
ARG2=$$(shuf -i 1-9 -n 2 | tr "\n" " ")
ARG3=$$(shuf -i 1-9 -n 3 | tr "\n" " ")
ARG4=$$(shuf -i 1-9 -n 4 | tr "\n" " ")
ARG6=$$(shuf -i 1-9 -n 6 | tr "\n" " ")
ARG7=$$(shuf -i 1-9 -n 7 | tr "\n" " ")
ARG8=$$(shuf -i 1-9 -n 8 | tr "\n" " ")
ARG9=$$(shuf -i 1-9 -n 9 | tr "\n" " ")
ARG10=$$(shuf -i 1-10 -n 10 | tr "\n" " ")
ARG3000=$$(shuf -i 1-100000 -n 3000 | tr "\n" " ")
test: re
	rm -f $(OBJ)
	clear
	-./$(NAME)
	@echo
	-./$(NAME) 54 54
	@echo
	-./$(NAME) "-43"
	@echo
	-./$(NAME) "42 42"
	@echo
	-./$(NAME) "voglio mangiare il tuo pancreas"
	@echo
	-./$(NAME) ""
	@echo
	-./$(NAME) "$(ARG1)"
	@echo
	-./$(NAME) "$(ARG2)"
	@echo
	-./$(NAME) "$(ARG3)"
	@echo
	-./$(NAME) "$(ARG4)"
	@echo
	-./$(NAME) "$(ARG5)"
	@echo
	-./$(NAME) "$(ARG6)"
	@echo
	-./$(NAME) "$(ARG7)"
	@echo
	-./$(NAME) "$(ARG8)"
	@echo
	-./$(NAME) "$(ARG9)"
	@echo
	-./$(NAME) "$(ARG10)"
	@echo
	-./$(NAME) "$(ARG3000)"
	@echo
	@rm -f $(NAME)

ARGS=1 3 2 9 6 8 4 7 5
# ARGS=$$(shuf -i 1-8 -n 9 | tr "\n" " ")
test2: re
	rm -f $(OBJ)
	clear
	-./$(NAME) "$(ARGS)"
	@rm -f $(NAME)

test3: re
	rm -f $(OBJ)
	clear
	-valgrind --leak-check=full ./$(NAME) "$(ARGS)"
	@rm -f $(NAME)

test4: re
	rm -f $(OBJ)
	clear
	-./$(NAME) "$(ARG3000)"
	@rm -f $(NAME)