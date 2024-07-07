NAME = minishell
CC = gcc
CLANG = clang
CFLAGS = -g -Wall -Werror -Wextra -I ./inc
SRC_DIR = src/obj
LIBFTPRINTF = lib/libftprintf.a
FIND = $(shell find $(SRC_DIR))
SRC = $(filter %.c, $(FIND))
OBJ = ${SRC:.c=.o}

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -C lib
		ar -rcs minishell.a $(OBJ)
		$(CLANG) $(CFLAGS) src/main.c minishell.a $(LIBFTPRINTF) -lreadline -o $(NAME)
		make clean
		clear

val: re
	make clean
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell

sup: re
	make clean
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=/home/aprado/42Projects/minishell/suppression/rline.supp ./minishell

clean:
		make -C lib clean
		rm -rf $(OBJ)
		clear

fclean: clean
		make -C lib fclean
		rm -rf minishell.a
		rm -rf $(NAME)
		clear

re: fclean all
