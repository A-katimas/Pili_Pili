NAME = codexion
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g


TOOLS_SRC = codexion_folders/parser.c \
			codexion_folders/utils.c \
			codexion_folders/init.c \
			codexion_folders/coder.c \
			codexion_folders/thread.c \
			codexion_folders/monitor.c \
			codexion_folders/dongle.c \
			codexion_folders/scheduler.c \
			codexion_folders/debug.c \
			codexion_folders/burnsecu.c \

# ORDERS_SRC = codexion.c

MAIN_SRC = main.c

ALL_SRC = $(TOOLS_SRC)
#$(MAIN_SRC)

OBJ = $(ALL_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) codexion_folders/main.c $(OBJ) -o $(NAME)

valgrind: re
	valgrind ./$(NAME) 5 150 100 100 10 5 1000000000 fifo
	valgrind --tool=helgrind ./$(NAME) 5 150 100 100 10 5 1000000000 fifo

test: re
	./$(NAME) 4 1000 200 200 100 5 200 edf

crach: re
	./$(NAME) 4 600 300 300 300 5 50 edf
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: test all clean fclean re