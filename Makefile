NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c \
       init.c \
       execute.c \
       utils.c \
       ft_strjoin.c \
       ft_split.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re