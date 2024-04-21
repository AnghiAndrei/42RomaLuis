# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebraho <ebraho@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 16:00:46 by ebraho            #+#    #+#              #
#    Updated: 2022/09/23 01:01:53 by ebraho           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = gcc -O2 -g
FLAGS  = -Wall -Wextra -Werror -g

NAME   = cub3d

INCLUDES = -I./includes

MLX = mlx

LIBFT = libft

SRCS = srcs/main.c \
		srcs/check_angles.c \
		srcs/check_borders.c \
		srcs/checker1.c \
		srcs/checker2.c \
		srcs/parser.c \
		srcs/raycaster_sprites.c \
		srcs/utils.c \
		srcs/utils2.c \
		srcs/image_utils.c \
		srcs/minimap.c \
		srcs/input_logic.c \
		srcs/render.c \
		srcs/render_walls.c \
		srcs/render_sprites.c \
		srcs/movement_handler.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: lib $(NAME)

lib:
	make -C $(MLX)
	make -C $(LIBFT)
	cp mlx/libmlx.dylib .

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(INCLUDES) -o $(NAME) $(LIBFT)/$(LIBFT).a -L$(MLX) -framework OpenGL -framework AppKit $(OBJS) libmlx.dylib

clean:
	make clean -C $(MLX)
	make clean -C $(LIBFT)
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)

fclean:
	rm -f $(NAME)
	rm -rf $(OBJS)
	rm -f libmlx.dylib
	make clean -C $(MLX)
	make fclean -C $(LIBFT)

re: fclean
	$(MAKE) all
