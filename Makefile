CLIENT_S := srcs/client.c
SERVER_S:= srcs/server.c
LIBFT:= libft/libft.a

FLAGS:= -Wall -Wextra -Werror
COMPILER:= clang

all: client server

client: $(CLIENT_S) $(LIBFT)
	$(COMPILER) $(FLAGS) $(CLIENT_S) $(LIBFT) -o client

server: $(SERVER_S) $(LIBFT)
	$(COMPILER) $(FLAGS) $(SERVER_S) $(LIBFT) -o server

$(LIBFT):
	make -C libft/


