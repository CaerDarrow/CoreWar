NAME = libft.a
SRC = $(wildcard mem/ft_*.c math/*.c str/ft_*.c print/ft_*.c vec/*.c gnl/get_next_line.c \
ADT/stack/*.c  ADT/list/*.c ADT/queue/*.c ADT/rb_tree/*.c)
OBJ = $(SRC:.c=.o)
GCCFLAGS = -Wall -Wextra -Werror -g -I ./includes/
.SILENT:
all: $(NAME)
$(OBJ): %.o:%.c
	gcc $(GCCFLAGS) -c $< -o $@
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
clean:
	/bin/rm -f $(OBJ)
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all
