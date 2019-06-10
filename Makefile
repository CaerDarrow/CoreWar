VM = corewar
ASM = asm
RM = /bin/rm -rf
CFLAGS = -Wall -Wextra -Werror -g -I libft/includes/
VM_SRC = vm/error.c vm/game.c vm/get_header.c vm/reader.c vm/vm.c vm/cursor.c \
vm/op.c vm/op_source_1.c vm/op_source_2.c vm/op_source_3.c vm/op_source_4.c \
vm/op_service.c vm/game_service.c vm/game_validation.c vm/apply_op.c \
vm/check.c vm/print_data.c vm/registers.c vm/read_args.c
ASM_SRC = $(wildcard assembler/*.c)

VM_OBJ = $(VM_SRC:.c=.o)
ASM_OBJ = $(ASM_SRC:.c=.o)
STORED_VM_OBJ = $(addprefix vm/obj/,$(notdir $(VM_OBJ)))
STORED_ASM_OBJ = $(addprefix assembler/obj/,$(notdir $(ASM_OBJ)))
LIBFT = libft/libft.a
PRINTF = libft/libftprintf.a
all: $(VM) $(ASM)
$(LIBFT):
	make -C libft
$(STORED_VM_OBJ): vm/obj/%.o:vm/%.c
	gcc $(CFLAGS) -c $< -o $@
$(STORED_ASM_OBJ): assembler/obj/%.o:assembler/%.c
	gcc $(CFLAGS) -c $< -o $@
	gcc $(CFLAGS) -c $< -o $@
$(VM): $(LIBFT) $(STORED_VM_OBJ)
	gcc $(CFLAGS) $(STORED_VM_OBJ) $(LIBFT) $(PRINTF) -o $(VM)
$(ASM): $(LIBFT) $(STORED_ASM_OBJ)
	gcc $(CFLAGS) $(STORED_ASM_OBJ) $(LIBFT) $(PRINTF) -o $(ASM)
clean:
	$(RM) $(STORED_VM_OBJ)
	$(RM) $(STORED_ASM_OBJ)
	$(RM) *.dSYM
	make -C libft clean
fclean: clean
	$(RM) $(VM)
	$(RM) $(ASM)
	make -C libft fclean
re: fclean all
