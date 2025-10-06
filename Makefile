NAME 				= pipex
SRCS 				= main.c string_utils.c split_utils.c io_utils.c
CFLAGS	 			= -Wall -Werror -Wextra
OBJS        	       	= $(SRCS:.c=.o)
CC 				= cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJS)
	
fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re