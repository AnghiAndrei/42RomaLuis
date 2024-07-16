# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/07/12 11:17:15 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRC = main.cpp marshal.cpp ../webserv.cpp ../execute.cpp ../path.cpp
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
	-./$(NAME) conf/error12.conf
	@echo
	-./$(NAME) conf/error13.conf
	@echo
	-./$(NAME) conf/error14.conf
	@echo
	-./$(NAME) conf/error15.conf
	@echo
	-./$(NAME) conf/error16.conf
	@echo
	-./$(NAME) conf/error17.conf
	@echo
	-./$(NAME) conf/error18.conf
	@echo
	-./$(NAME) conf/error19.conf
	@echo
	-./$(NAME) conf/error20.conf
	@echo
	-./$(NAME) conf/error21.conf
	@echo
	-./$(NAME) conf/error22.conf
	@echo
	-./$(NAME) conf/error23.conf
	@echo
	-./$(NAME) conf/error24.conf
	@echo
	-./$(NAME) conf/error25.conf
	@echo
	-./$(NAME) conf/error26.conf
	@echo
	-./$(NAME) conf/error27.conf
	@echo
	-./$(NAME) conf/error28.conf
	@echo
	-./$(NAME) conf/error29.conf
	@echo
	-./$(NAME) conf/error30.conf
	@echo
	-./$(NAME) conf/error31.conf
	@echo
	-./$(NAME) conf/error32.conf
	@echo
	-./$(NAME) conf/error33.conf
	@echo
	-./$(NAME) conf/error34.conf
	@echo
	-./$(NAME) conf/error35.conf
	@echo
	-./$(NAME) conf/error36.conf
	@echo
	@rm -f $(NAME)

test2: re
	rm -f $(OBJ)
	clear
	@echo "=====> Casi in cui deve funzionare <====="
	-./$(NAME)
	@echo
	-./$(NAME) conf/conffull.conf
	@echo
	-./$(NAME) conf/conf1.conf
	@echo
	-./$(NAME) conf/conf2.conf
	@echo
	@rm -f $(NAME)