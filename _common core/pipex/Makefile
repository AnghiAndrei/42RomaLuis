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

test-leaks-m: re
	@rm -f infile
	@clear
	@echo ================= Mandatori: controllo dell input =================
	-valgrind ./pipex
	@echo
	-valgrind ./pipex infile
	@echo
	-valgrind ./pipex infile ls
	@echo
	-valgrind ./pipex infile ls wc
	@echo
	@echo "! Nota: Deve dare errore perche il file: infile; non esiste !"
	-valgrind ./pipex infile ls cat outfile
	@echo
	@echo "                 ==== Creazione file: infile ===="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	@echo "             ==== Controllo esistenza dei comandi ===="
	-valgrind ./pipex infile aanghi cat outfile
	@echo
	-valgrind ./pipex infile ls aanghi outfile
	@echo ==================== Mandatori: function check ====================
	-valgrind ./pipex infile "ls -la" "grep .c" outfile
	@echo ! E errore se il file: outfile, non ha i permessi di lettura/scrittura !
	@cat outfile
	@-< infile ls -la | grep .c > outfile2
	@echo ! Se i 2 output non sono uguali e considerato errore !
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-valgrind ./pipex infile "grep hola" "cat -e" outfile
	@-< infile grep hola | cat -e > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-leaks-b: bonus
	@rm -f infile
	@clear
	@echo ================= Bonus: controllo dell input =================
	-valgrind ./pipex_bonus
	@echo
	-valgrind ./pipex_bonus infile
	@echo
	-valgrind ./pipex_bonus infile ls
	@echo
	-valgrind ./pipex_bonus infile ls wc
	@echo
	@echo "! Nota: Deve dare errore perche il file: infile; non esiste !"
	-valgrind ./pipex_bonus infile ls cat outfile
	@echo
	@echo "                 ==== Creazione file: infile ===="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	@echo "             ==== Controllo esistenza dei comandi ===="
	-valgrind ./pipex_bonus infile aanghi cat outfile
	@echo
	-valgrind ./pipex_bonus infile ls aanghi outfile
	@echo ==================== Bonus: function check ====================
	-valgrind ./pipex_bonus infile "ls -la" "grep .c" outfile
	@echo ! E errore se il file: outfile, non ha i permessi di lettura/scrittura !
	@cat outfile
	@-< infile ls -la | grep .c > outfile2
	@echo ! Se i 2 output non sono uguali e considerato errore !
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-valgrind ./pipex_bonus infile "grep hola" "cat -e" outfile
	@-< infile grep hola | cat -e > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-valgrind ./pipex infile "echo voglio mangiare il tuo pancreas" "grep pancreas" "tr a-z A-Z" "head -n 1" "cat -e" "wc -l" outfile
	< infile echo voglio mangiare il tuo pancreas | grep pancreas | tr a-z A-Z | head -n 1 | cat -e | wc -l > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo "                ===== CONTROLLO HERE_DOC ====="
	@echo "! Il file: outfile; deve contenere una righa vuota all inizio !"
	-valgrind ./pipex here_doc fine "grep 42" "cat -e" "wc" outfile
	-grep 42 << fine | cat -e | wc >> outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks-m: re
	@rm -f infile
	@clear
	@echo ================= Mandatori: controllo dell input =================
	-./pipex
	@echo
	-./pipex infile
	@echo
	-./pipex infile ls
	@echo
	-./pipex infile ls wc
	@echo
	@echo "! Nota: Deve dare errore perche il file: infile; non esiste !"
	-./pipex infile ls cat outfile
	@echo
	@echo "                 ==== Creazione file: infile ===="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	@echo "             ==== Controllo esistenza dei comandi ===="
	-./pipex infile aanghi cat outfile
	@echo
	-./pipex infile ls aanghi outfile
	@echo ==================== Mandatori: function check ====================
	-./pipex infile "ls -la" "grep .c" outfile
	@echo ! E errore se il file: outfile, non ha i permessi di lettura/scrittura !
	@cat outfile
	@-< infile ls -la | grep .c > outfile2
	@echo ! Se i 2 output non sono uguali e considerato errore !
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-./pipex infile "grep hola" "cat -e" outfile
	@-< infile grep hola | cat -e > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks-b: bonus
	@rm -f infile
	@clear
	@echo ================= Bonus: controllo dell input =================
	-./pipex_bonus
	@echo
	-./pipex_bonus infile
	@echo
	-./pipex_bonus infile ls
	@echo
	-./pipex_bonus infile ls wc
	@echo
	@echo "! Nota: Deve dare errore perche il file: infile; non esiste !"
	-./pipex_bonus infile ls cat outfile
	@echo
	@echo "                 ==== Creazione file: infile ===="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	@echo "             ==== Controllo esistenza dei comandi ===="
	-./pipex_bonus infile aanghi cat outfile
	@echo
	-./pipex_bonus infile ls aanghi outfile
	@echo ==================== Bonus: function check ====================
	-./pipex_bonus infile "ls -la" "grep .c" outfile
	@echo ! E errore se il file: outfile, non ha i permessi di lettura/scrittura !
	@cat outfile
	@-< infile ls -la | grep .c > outfile2
	@echo ! Se i 2 output non sono uguali e considerato errore !
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-./pipex_bonus infile "grep hola" "cat -e" outfile
	@-< infile grep hola | cat -e > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-./pipex infile "echo voglio mangiare il tuo pancreas" "grep pancreas" "tr a-z A-Z" "head -n 1" "cat -e" "wc -l" outfile
	< infile echo voglio mangiare il tuo pancreas | grep pancreas | tr a-z A-Z | head -n 1 | cat -e | wc -l > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo "                ===== CONTROLLO HERE_DOC ====="
	@echo "! Il file: outfile; deve contenere una righa vuota all inizio !"
	-./pipex here_doc fine "grep 42" "cat -e" "wc" outfile
	-grep 42 << fine | cat -e | wc >> outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-norm:
	@echo Errori di norma:
	@norminette *.c *.h | grep Error! | wc -l
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

