# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/05/02 10:36:38 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Conversion_of_scalar_types
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp ScalarConverter.cpp
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

test: re
	rm -f $(OBJ)
	clear
	./$(NAME) 0
	./$(NAME) 42
	./$(NAME) -42
	./$(NAME) nan
	./$(NAME) 42.0f
	@rm -f $(NAME)