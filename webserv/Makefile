# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/06/24 17:26:25 by aanghi           ###   ########.fr        #
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
	@echo "=====> Casi in cui non deve funzionare <====="
	-./$(NAME) piu parametri
	@echo
	-./$(NAME) no_exsist.conf
	@echo
	-./$(NAME) conf/error1.conf
	@echo
	-./$(NAME) conf/error2.conf
	@echo
	-./$(NAME) conf/error3.conf
	@echo
	@echo "=====> Casi in cui deve funzionare <====="
	-./$(NAME)
	@echo
	-./$(NAME) conf/conf1.conf
	@echo
	@rm -f $(NAME)