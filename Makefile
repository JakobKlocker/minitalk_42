NAME = client
SRC = ./client/main.c
OBJ = $(SRC:.c=.o)
CC = cc
FLAG = -Wall -Werror -Wextra
OPTION = -o

all: $(NAME)

$(NAME):
		$(MAKE) all -C ./libft
		$(CC) $(OPTION) client $(FLAG) ./client_dir/client.c ./libft/libft.a
		$(CC) $(OPTION) server $(FLAG) ./server_dir/server.c ./libft/libft.a
clean: 
		$(MAKE) clean -C ./libft

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f client
		rm -f server

re:		fclean all

bonus:
		$(MAKE) all -C ./libft
		$(CC) $(OPTION) client $(FLAG) ./bonus/client_bonus.c ./libft/libft.a
		$(CC) $(OPTION) server $(FLAG) ./bonus/server_bonus.c ./libft/libft.a

.PHONY: all bonus clean fclean re