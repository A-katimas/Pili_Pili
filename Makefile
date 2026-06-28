NAME = codexion
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread


TOOLS_SRC = parser.c \
			utils.c \
			init.c \
			log.c \
			coder.c \
			thread.c \
			monitor.c \
			dongle.c \
			scheduler.c \
			debug.c \

# ORDERS_SRC = codexion.c

MAIN_SRC = main.c

ALL_SRC = $(TOOLS_SRC)
#$(MAIN_SRC)

OBJ = $(ALL_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) main.c $(OBJ) -o $(NAME)

valgrind: re
	valgrind --leak-check=full ./$(NAME) 5 1000 100 100 10 5 100 fifo

test: re
	./$(NAME) 4 800 200 200 100 5 50 edf

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: test all clean fclean re