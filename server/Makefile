NAME	=	server

SRC	= 	main.cpp \
				network/tcp_connection.cpp \
				network/tcp_server.cpp

OBJ		=	$(SRC:.cpp=.o)

CFLAGS	= #-Wall -Wextra -Werror

LDFLAGS = -lboost_system -lpthread -lboost_iostreams -lboost_serialization

INCLUDE = -I /usr/local/boost_1_67_0/

CC		=	g++

RM		=	rm -f
ECHO	=	echo -e

%.o: %.cpp
	$(CC) -c $(INCLUDE) -o  $@ $< $(CFLAGS)

all	: $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LDFLAGS)
	@$(ECHO) '\033[0;33m> Compiled\033[0m'

clean	:
	$(RM) $(OBJ)
	@$(ECHO) '\033[0;33m> Directory cleaned\033[0m'

fclean	: clean
	$(RM) $(NAME)
	@$(ECHO) '\033[0;33m> Remove executable\033[0m'

re	: fclean all
