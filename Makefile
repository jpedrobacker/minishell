NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I ./inc
SRC_DIR = src/obj
LIBFTPRINTF = lib/libftprintf.a
FIND = $(shell find $(SRC_DIR))
SRC = $(filter %.c, $(FIND))
OBJ = ${SRC:.c=.o}

SOURCES = src/main.c \
	  src/path_utils.c \
	  src/linked_list_func.c \
	  src/utils.c

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -C lib
		$(CC) $(CFLAGS) $(SOURCES) $(OBJ) $(LIBFTPRINTF) $(LIBFT) -lreadline -o $(NAME)

clean:
		make -C lib clean
		rm -rf $(OBJ)

fclean: clean
		make -C lib fclean
		rm -rf $(NAME)

re: fclean all
