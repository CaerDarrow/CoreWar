ASM = asm
VM = corewar
CFLAGS = -Wall -Wextra -Werror -g -I libft/includes/
VM_SRC = vm/error.c vm/game.c vm/get_header.c vm/reader.c vm/vm.c vm/cursor.c \
vm/op.c
ASM_SRC = assembler/*.c
VM_OBJ = $(VM_SRC:.c=.o)
ASM_OBJ = $(ASM_SRC:.c=.o)
LIBFT = libft/libft.a
PRINTF = libft/libftprintf.a
all: $(ASM) $(VM)
$(LIBFT):
	make -C libft
$(VM_OBJ): $(VM_SRC)
	gcc -c $(CFLAGS) $(VM_SRC)
	mv *.o vm/
$(ASM_OBJ): $(ASM_SRC)
	gcc -c $(CFLAGS) $(ASM_SRC)
	mv *.o assembler/
$(VM): $(LIBFT) $(VM_OBJ)
	gcc $(CFLAGS) $(VM_OBJ) $(LIBFT) $(PRINTF) -o $(VM)
$(ASM): $(LIBFT) $(ASM_OBJ)
	gcc $(CFLAGS) $(ASM_OBJ) $(LIBFT) $(PRINTF) -o $(ASM)

clean:
	/bin/rm -rf $(VM_OBJ)
	/bin/rm -rf $(ASM_OBJ)
	/bin/rm -rf *.dSYM
	make -C libft clean
fclean: clean
	/bin/rm -rf $(ASM)
	/bin/rm -rf $(VM)
	make -C libft fclean
re: fclean all
