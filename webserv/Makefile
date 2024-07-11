# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/07/11 14:07:23 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv
CFLAGS = #-Wall -Wextra -Werror -std=c++98 -g

SRC = main.cpp marshal/marshal.cpp webserv.cpp execute.cpp path.cpp
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
	-./$(NAME) conf/simpconf.conf
	@rm -f $(NAME)

test2: re
	rm -f $(OBJ)
	clear
	-valgrind ./$(NAME) conf/simpconf.conf
	@rm -f $(NAME)
