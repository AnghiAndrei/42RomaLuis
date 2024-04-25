# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/04/25 13:14:46 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Sed_is_for_losers
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp
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
	echo "hola" >> temp.txt
	echo "gdholafd" >> temp.txt
	clear
	./$(NAME) temp.txt hola "voglio mangiare il tuo pancreas"
	cat temp.txt
	cat temp.txt.replace
	@rm -f temp.txt.replace
	@rm -f temp.txt
	@rm -f $(NAME)