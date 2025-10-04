NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
SRC = main.c process.c
OBJ = $(SRC:.c=.o)
HEADER = pipex.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

clean:
	rm -f $(OBJ)
	@$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
