# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/03/05 17:00:26 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = TheJobOfYourDreams
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = test.cpp Account.cpp
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	g++ $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

git: fclean
	@git add .
	@git commit -m "voglio mangiare il tuo pancreas"
	@git push

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

test: re
	rm -f $(OBJ)
	clear
	./$(NAME)
	@rm -f $(NAME)