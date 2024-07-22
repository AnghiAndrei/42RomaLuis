# AUTHOR:	@AYoungSn @mocha-kim
# PUBLISH:	2022/02

NAME = webserv

SRCS_PATH		= ./srcs
INCS_PATH		= ./includes

SRCS			= $(SRCS_PATH)/main.cpp \
					$(SRCS_PATH)/Server.cpp $(SRCS_PATH)/Location.cpp \
					$(SRCS_PATH)/Client.cpp $(SRCS_PATH)/Utils.cpp \
					$(SRCS_PATH)/Request.cpp $(SRCS_PATH)/Response.cpp \
					$(SRCS_PATH)/ServerManager.cpp $(SRCS_PATH)/ServerManagerHelper.cpp\
					$(SRCS_PATH)/ConfigParser.cpp $(SRCS_PATH)/CgiHandler.cpp

OBJS			= $(SRCS:.cpp=.o)

CXX				= g++
CXXFLAGS		= -Wall -Werror -Wextra -std=c++98
# CXXFLAGS		= -std=c++98 -fsanitize=address

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -I $(INCS_PATH) -o $(NAME) $(OBJS)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re