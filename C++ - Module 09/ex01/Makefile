# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/06/05 11:01:27 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RPN
CFLAGS = -Wall -Wextra -Werror -g -std=c++98

SRC = main.cpp RPN.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

%.o: %.cpp
	c++ $(CFLAGS) -c $< -o $@

test: re
	@rm -f $(OBJ)
	@clear
	-./$(NAME)
	@echo
	-./$(NAME) ""
	@echo
	-./$(NAME) "42"
	@echo
	-./$(NAME) "4 4"
	@echo
	-./$(NAME) "4 4 "
	@echo
	-./$(NAME) "1 2 * 2 4 -"
	@echo
	-./$(NAME) "1 2 * 2 4 - 4"
	@echo
	-./$(NAME) "1 2 * 2 - -"
	@echo
	-./$(NAME) "4"
	@echo
	-./$(NAME) "4 "
	@echo
	-./$(NAME) "9 9 +"
	@echo
	-./$(NAME) "9 9 -"
	@echo
	-./$(NAME) "9 9 *"
	@echo
	-./$(NAME) "9 9 /"
	@echo
	-./$(NAME) "4 2 2 * -"
	@echo
	-./$(NAME) "7 7 * 7 -"
	@echo
	-./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	@echo
	-./$(NAME) "(1 + 1)"
	@echo
	-./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	@echo
	-./$(NAME) "9 8 * 4 * 4 / 2 + 9 - 8 - 8 - 1 - 6 -"
	@echo
	-./$(NAME) "1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 /"
	@echo
	@rm -f $(NAME)