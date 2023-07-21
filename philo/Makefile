CC = gcc -pthread

NAME = philo

MY_SOURCES = main.c utils.c thread.c state.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -ggdb3

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	$(CC) $(CFLAGS) $(MY_OBJECTS) -o $(NAME)

debug: $(MY_OBJECTS)
	$(CC) $(CFLAGS) $(MY_OBJECTS) -fsanitize=address -o $(NAME)

RM=rm -f

clean:
	$(RM) $(MY_OBJECTS)

fclean: clean
	${RM} ${NAME}

re:	fclean all