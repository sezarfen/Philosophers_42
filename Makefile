NAME=philo
SRCS=info.c main.c philosopher.c times.c utils.c
OBJS=$(SRCS:.c=.o)
CFLAGS= -Werror -Wall -Wextra
CC=gcc
PT=-pthread #-fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(PT) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
