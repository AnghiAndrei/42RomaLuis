# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/06/05 21:21:08 by aanghi           ###   ########.fr        #
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

ARG5=$$(shuf -i 1-100 -n 5 | tr "\n" " ")
ARG10=$$(shuf -i 1-100 -n 10 | tr "\n" " ")
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
	-./$(NAME) "voglio mangiare il tuo pancreas"
	@echo
	-./$(NAME) ""
	@echo
	-./$(NAME) "$(ARG5)"
	@echo
	-./$(NAME) "$(ARG10)"
	@echo
	-./$(NAME) "$(ARG3000)"
	@echo
	@rm -f $(NAME)

ARGS=$$(shuf -i 1-100 -n 15 | tr "\n" " ")
test2: re
	rm -f $(OBJ)
	clear
	-./$(NAME) "$(ARGS)"
	@rm -f $(NAME)