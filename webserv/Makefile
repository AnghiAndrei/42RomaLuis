# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/06/04 15:24:36 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv
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
	clear
	@echo Senza parametri
	-./$(NAME)
	@echo Piu parametri
	-./$(NAME) piu parametri
	@echo File inesistente
	-./$(NAME) no_exsist.conf
	@echo File vuoto
	-./$(NAME) conf/error1.conf
	@echo
	@rm -f $(NAME)