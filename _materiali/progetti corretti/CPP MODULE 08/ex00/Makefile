# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 18:46:47 by lde-mich          #+#    #+#              #
#    Updated: 2024/03/04 16:49:13 by lde-mich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= $(wildcard *.cpp)

OBJS			= $(SRCS:.cpp=.o)


CC				= c++
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -std=c++98


RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
RESET	= \033[0;0m


NAME			= easyFind

%.o:%.cpp
				@$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
				@printf "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
				@printf "$(GREEN)$(NAME) initialized\n$(RESET)"
				@printf "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"

all:			$(NAME)

clean:
				@printf "$(RED)\nRemoving Object files...\n$(RESET)"
				@printf "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
				@$(RM) $(OBJS)
				@printf "$(RED)Object files removed\n$(RESET)"

fclean:			clean
				@printf "$(RED)\nRemoving program executable...\n$(RESET)"
				@printf "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
				@$(RM) $(NAME)
				@printf "$(RED)$(NAME) removed\n$(RESET)"

re:				fclean $(NAME)


.PHONY:			all clean fclean re bonus
