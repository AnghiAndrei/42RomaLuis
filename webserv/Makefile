# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/06/24 23:17:59 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

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
	-./$(NAME) conf/error4.conf
	@echo
	-./$(NAME) conf/error5.conf
	@echo
	-./$(NAME) conf/error6.conf
	@echo
	-./$(NAME) conf/error7.conf
	@echo
	-./$(NAME) conf/error8.conf
	@echo
	-./$(NAME) conf/error9.conf
	@echo
	-./$(NAME) conf/error10.conf
	@echo
	-./$(NAME) conf/error11.conf
	@echo
	@echo "=====> Casi in cui deve funzionare <====="
	-./$(NAME)
	@echo
	-./$(NAME) conf/conf1.conf
	@echo
	@rm -f $(NAME)

test2: re
	rm -f $(OBJ)
	clear
	-valgrind ./$(NAME) conf/error7.conf
	@echo
	@rm -f $(NAME)