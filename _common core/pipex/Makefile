# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/06/20 16:02:47 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =   pipex
NAMEB =   pipex_bonus
CFLAGS = -Wall -Wextra -Werror

SRC = main.c utilis.c marshal.c \
	  get_args.c get_args_utilis.c \
	  get_next_line.c get_next_line_utils.c \
	  ft_strlen.c ft_split.c ft_strncmp.c ft_substr.c ft_strjoin.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJ)
	gcc -o $(NAMEB) $(OBJ)

git:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -f $(NAME)
	@rm -f .DS_Store
	@git add .
	@git commit -m "commit"
	@git push

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

test: re
	chmod 777 $(NAME)
	@touch infile
	@rm -f $(OBJ)
	./pipex infile "ls -la" "grep .c" "wc -l" outfile
	@cat outfile
	@rm outfile
	< infile ls -la | grep .c | wc -l > outfile
	@cat outfile
	@rm outfile
	@echo ---------------------------------
	./pipex infile "echo 'il senzo della vita: 42\0'" "grep 42" "tr a-z A-Z" "head -10" "cat -e" "wc -l" outfile
	@cat outfile
	@rm outfile
	< infile echo 'il senzo della vita: 42\0' | grep 42 | tr a-z A-Z | head -10 | cat -e | wc -l > outfile
	@cat outfile
	@rm outfile
	@echo ---------------------------------
	@echo " a" > infile
	@echo " a" >> infile
	@echo " g" >> infile
	@echo " a" >> infile
	@echo "a" >> infile
	@echo "a" >> infile
	./pipex infile "grep ' '" "grep a" "head -10" "cat -e" "wc -l" outfile
	@cat outfile
	@rm outfile
	< infile grep ' ' | grep a | head -10 | cat -e | wc -l > outfile
	@cat outfile
	@echo ---------------------------------
	@rm infile
	@echo "===== CONTROLLO HERE_DOC ====="
	./pipex here_doc fine "grep '42'" "grep ' '" "cat -e" "wc" outfile
	@cat outfile
	grep 42 << fine | grep ' ' | cat -e | wc >> outfile
	@cat outfile
	@rm outfile
	@echo ---------------------------------
	@rm -f $(NAME)

