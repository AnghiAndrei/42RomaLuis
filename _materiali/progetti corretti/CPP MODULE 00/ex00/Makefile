# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 20:22:55 by fcarlucc          #+#    #+#              #
#    Updated: 2024/01/10 14:06:50 by fcarlucc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Megaphone

SRC = $(wildcard *.cpp) \

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Werror -Wextra -std=c++98

CC = c++

RM = rm -rf

#COLORS
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

DEFAULT = \033[0m

all : $(NAME)

%.o : %.cpp
	@(c++ $(FLAGS) -c $< -o $@)

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@rm -f $(OBJ)
	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)all deleted!$(DEFAULT)"

re: fclean all

.PHONY:	all clean fclean re
