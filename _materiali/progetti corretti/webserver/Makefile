NAME = webserv

CC = c++

FLAGS = -std=c++98 -Wall -Wextra -Werror -pedantic -ansi

FILES = $(wildcard *.cpp) $(wildcard parser_conf/*.cpp) $(wildcard server/*.cpp) $(wildcard conf/*.cpp) $(wildcard error/*.cpp) $(wildcard utilities/*.cpp) $(wildcard request/*.cpp) $(wildcard get/*.cpp) $(wildcard post/*.cpp) $(wildcard delete/*.cpp) $(wildcard cgi/*.cpp) 
OBJ=$(FILES:.cpp=.o)

HEADER = 

%.o:%.cpp $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(FILES) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
