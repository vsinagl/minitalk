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

server_old: srcs/server_old.c $(LIBFT)
	$(COMPILER) $(FLAGS) srcs/server_old.c $(LIBFT) -o server_old

clean:

fclean:
	@[ -f client ] && rm client || true
	@[ -f server ] && rm server || true
	@[ -f server_old ] && rm server_old || true
	@echo "remove binaries"

$(LIBFT):
	make -C libft/


