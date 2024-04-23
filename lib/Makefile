SRCS	=		ft_printf.c \
				ft_printf_char.c \
				ft_printf_str.c \
				ft_printf_nbr.c \
				ft_printf_pointer.c \
				ft_printf_percent.c \
				ft_printf_unsigned.c \
				ft_printf_hexadecimal.c \
				ft_utilities.c \

OBJ			=	$(SRCS:.c=.o)
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
NAME		=	libftprintf.a
LIBFTNAME	=	libft.a
LIBFTDIR	=	./libft

all: $(NAME)

makelib:
		make -C $(LIBFTDIR)
		cp $(LIBFTDIR)/$(LIBFTNAME) .
		mv $(LIBFTNAME) $(NAME)
		make clean

$(NAME): makelib $(OBJ)
		ar -rcs $(NAME) $(OBJ)

clean:
		rm -rf $(OBJ)
		cd $(LIBFTDIR) && make clean

fclean: clean
		rm -rf $(NAME)
		cd $(LIBFTDIR) && make fclean

re: fclean all
