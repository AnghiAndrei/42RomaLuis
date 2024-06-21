# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 17:55:23 by aanghi            #+#    #+#              #
#    Updated: 2024/06/21 13:23:22 by aanghi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKEFLAGS += -s

NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
ARG = maps/1.cub

MINILIBX_PATH = ./mlx
MINILIBX = $(MINILIBX_PATH)/libmlx.a

SRC = \
	  ft_split.c ft_strlen.c ft_strncmp.c ft_substr.c ft_strjoin.c ft_atoi.c \
	  print_map_utilitis.c print_map.c print_minimap.c \
	  get_next_line.c get_next_line_utils.c \
	  main.c marshal.c controlls.c \
	  game_init.c game_init1.c \
	  utilitis.c utilitis1.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(MINILIBX)
	gcc $(OBJ) $(CFLAGS) $(MINILIBX) mlx/libmlx.a -L./mlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

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
	gcc $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(MINILIBX):
	chmod 777 $(MINILIBX_PATH)/configure
	make -C $(MINILIBX_PATH)

test: re
	rm -f $(OBJ)
	clear
	echo /$(NAME)
	-./$(NAME)
	echo
	echo /$(NAME) maps/1.cub maps/2.cub
	-./$(NAME) maps/1.cub maps/2.cub
	echo
	echo /$(NAME) maps/no_exist.cub
	-./$(NAME) maps/no_exist.cub
	echo
	echo /$(NAME) maps/1.angly
	-./$(NAME) maps/1.angly
	echo
	echo /$(NAME) maps/error1.cub
	-./$(NAME) maps/error1.cub
	echo
	echo /$(NAME) maps/error2.cub
	-./$(NAME) maps/error2.cub
	echo
	echo /$(NAME) maps/error3.cub
	-./$(NAME) maps/error3.cub
	echo
	echo /$(NAME) maps/error4.cub
	-./$(NAME) maps/error4.cub
	echo
	echo /$(NAME) maps/error5.cub
	-./$(NAME) maps/error5.cub
	echo
	echo /$(NAME) maps/error6.cub
	-./$(NAME) maps/error6.cub
	echo
	echo /$(NAME) maps/error7.cub
	-./$(NAME) maps/error7.cub
	echo
	echo /$(NAME) maps/error8.cub
	-./$(NAME) maps/error8.cub
	echo
	echo /$(NAME) maps/error9.cub
	-./$(NAME) maps/error9.cub
	echo
	echo /$(NAME) maps/error10.cub
	-./$(NAME) maps/error10.cub
	@rm -f $(NAME)

test2: re
	rm -f $(OBJ)
	clear
	echo valgrind ./$(NAME) $(ARG)
	valgrind --leak-check=full --track-origins=yes ./$(NAME) $(ARG)
#valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARG)
#valgrind --leak-check=full ./$(NAME) $(ARG)
	@echo Norminette error: 
	norminette $(SRC) cub3d.h | grep Error! | wc -l
	@echo
# @leaks -atExit -- ./$(NAME) > temp.txt
# cat temp.txt | grep "total leaked bytes."
# rm temp.txt	
	@rm -f $(NAME)

test3: re
	rm -f $(OBJ)
	clear
	echo ./$(NAME) $(ARG)
	./$(NAME) $(ARG)
	@rm -f $(NAME)

norm:
	norminette $(SRC) cub3d.h


test-leaks: re
	@clear
	@echo Senza parametri
	-valgrind ./cub3D
	@echo
	@echo Piu di un parametro
	-valgrind ./cub3D maps/1.cub maps/2.cub
	@echo
	@echo Mappa inesistente
	-valgrind ./cub3D maps/no_exist.cub
	@echo
	@echo Mappa non .aanghi
	-valgrind ./cub3D maps/1.aanghi
	@echo
	@echo Manca la configurazione del soffitto
	-valgrind ./cub3D maps/error1.cub
	@echo
	@echo Manca la mappa
	-valgrind ./cub3D maps/error2.cub
	@echo
	@echo 0 player nella mappa
	-valgrind ./cub3D maps/error3.cub
	@echo
	@echo 1+ player nella mappa
	-valgrind ./cub3D maps/error4.cub
	@echo
	@echo Mappa aperta con lo 0
	-valgrind ./cub3D maps/error5.cub
	@echo
	@echo Mappa aperta con lo  
	-valgrind ./cub3D maps/error6.cub
	@echo
	@echo Spazi nella configurazione dei colori
	-valgrind ./cub3D maps/error7.cub
	@echo
	@echo Assente configurazione dei colori
	-valgrind ./cub3D maps/error8.cub
	@echo
	@echo Numero negativo nella configurazione dei colori
	-valgrind ./cub3D maps/error9.cub
	@echo
	@echo Numero oltre 255 nella configurazione dei colori
	-valgrind ./cub3D maps/error10.cub
	@echo
	@echo File vuoto
	-valgrind ./cub3D maps/error11.cub
	@echo
	@echo Assente configurazione delle texture
	-valgrind ./cub3D maps/error12.cub
	@echo
	@echo Texture inesistente
	-valgrind ./cub3D maps/error13.cub
	@echo
	@echo Riga vuota nella mappa
	-valgrind ./cub3D maps/error14.cub
	@echo
	@echo Riga vuota nel file
	-valgrind ./cub3D maps/error15.cub
	@echo
	@echo Player fuori dalla mappa
	-valgrind ./cub3D maps/error16.cub
	@echo
	@echo Mappa prima della configurazione
	-valgrind ./cub3D maps/error17.cub
	@echo
	@echo Spazi dentro la mappa
	-valgrind ./cub3D maps/error18.cub
	@echo
	@echo Carattere inaspettato
	-valgrind ./cub3D maps/error19.cub
	@echo
	@echo Configurazione dei colori in piu. Ex 1,1,1,1
	-valgrind ./cub3D maps/error20.cub
	@echo
	@echo Configurazione delle texture in piu. Ex ./NO.xpm ./NO2.xpm
	-valgrind ./cub3D maps/error21.cub
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks: re
	@clear
	@echo Senza parametri
	-./cub3D
	@echo
	@echo Piu di un parametro
	-./cub3D maps/1.cub maps/2.cub
	@echo
	@echo Mappa inesistente
	-./cub3D maps/no_exist.cub
	@echo
	@echo Mappa non .aanghi
	-./cub3D maps/1.aanghi
	@echo
	@echo Manca la configurazione del soffitto
	-./cub3D maps/error1.cub
	@echo
	@echo Manca la mappa
	-./cub3D maps/error2.cub
	@echo
	@echo 0 player nella mappa
	-./cub3D maps/error3.cub
	@echo
	@echo 1+ player nella mappa
	-./cub3D maps/error4.cub
	@echo
	@echo Mappa aperta con lo 0
	-./cub3D maps/error5.cub
	@echo
	@echo Mappa aperta con lo  
	-./cub3D maps/error6.cub
	@echo
	@echo Spazi nella configurazione dei colori
	-./cub3D maps/error7.cub
	@echo
	@echo Assente configurazione dei colori
	-./cub3D maps/error8.cub
	@echo
	@echo Numero negativo nella configurazione dei colori
	-./cub3D maps/error9.cub
	@echo
	@echo Numero oltre 255 nella configurazione dei colori
	-./cub3D maps/error10.cub
	@echo
	@echo File vuoto
	-./cub3D maps/error11.cub
	@echo
	@echo Assente configurazione delle texture
	-./cub3D maps/error12.cub
	@echo
	@echo Texture inesistente
	-./cub3D maps/error13.cub
	@echo
	@echo Riga vuota nella mappa
	-./cub3D maps/error14.cub
	@echo
	@echo Riga vuota nel file
	-./cub3D maps/error15.cub
	@echo
	@echo Player fuori dalla mappa
	-./cub3D maps/error16.cub
	@echo
	@echo Mappa prima della configurazione
	-./cub3D maps/error17.cub
	@echo
	@echo Spazi dentro la mappa
	-./cub3D maps/error18.cub
	@echo
	@echo Carattere inaspettato
	-./cub3D maps/error19.cub
	@echo
	@echo Configurazione dei colori in piu. Ex 1,1,1,1
	-./cub3D maps/error20.cub
	@echo
	@echo Configurazione delle texture in piu. Ex ./NO.xpm ./NO2.xpm
	-./cub3D maps/error21.cub
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-norm:
	@echo Errori di norma:
	@norminette *.c *.h | grep Error! | wc -l
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

