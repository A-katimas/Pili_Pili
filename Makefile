NAME = codexion
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread


TOOLS_SRC = codexion.c \
			parser.c \
			utils.c

# ORDERS_SRC = codexion.c

MAIN_SRC = main.c

ALL_SRC = $(TOOLS_SRC)
#$(MAIN_SRC)

OBJ = $(ALL_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) main.c $(OBJ) -o $(NAME)


test: re
	./$(NAME) 10 1009 1000 1000 1000 5 2000 fifo

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: test all clean fclean re