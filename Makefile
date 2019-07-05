VM = corewar
ASM = asm
RM = /bin/rm -rf
CFLAGS = -Wall -Wextra -Werror -g -I libft/includes/
VM_SRC = $(wildcard vm/*.c)
VIS_SRC = $(wildcard vm/vis/*.c)
ASM_SRC = $(wildcard assembler/*.c)
VM_OBJ = $(VM_SRC:.c=.o)
VIS_OBJ = $(VIS_SRC:.c=.o)
ASM_OBJ = $(ASM_SRC:.c=.o)
STORED_VM_OBJ = $(addprefix vm/obj/,$(notdir $(VM_OBJ)))
STORED_ASM_OBJ = $(addprefix assembler/obj/,$(notdir $(ASM_OBJ)))
STORED_VIS_OBJ = $(addprefix vm/vis/obj/,$(notdir $(VIS_OBJ)))
MLX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
LIBFT = libft/libft.a
PRINTF = libft/libftprintf.a
all: $(VM) $(ASM)
lib:
	make -C libft
$(LIBFT):
	make -C libft
$(STORED_VM_OBJ): vm/obj/%.o:vm/%.c
	gcc $(CFLAGS) -c $< -o $@
$(STORED_ASM_OBJ): assembler/obj/%.o:assembler/%.c
	gcc $(CFLAGS) -c $< -o $@
vm/obj:
	mkdir vm/obj
vm/vis/obj:
	mkdir vm/vis/obj
assembler/obj:
	mkdir assembler/obj
$(STORED_VIS_OBJ): vm/vis/obj/%.o:vm/vis/%.c
	gcc $(CFLAGS) -I vm/ -c $< -o $@
$(VM): $(LIBFT) vm/obj vm/vis/obj $(STORED_VM_OBJ) $(STORED_VIS_OBJ)
	gcc $(CFLAGS) $(MLX) $(STORED_VM_OBJ) $(STORED_VIS_OBJ) $(LIBFT) $(PRINTF) -o $(VM)
$(ASM): $(LIBFT) assembler/obj $(STORED_ASM_OBJ)
	gcc $(CFLAGS) $(STORED_ASM_OBJ) $(LIBFT) $(PRINTF) -o $(ASM)
clean:
	$(RM) $(STORED_VM_OBJ)
	$(RM) $(STORED_ASM_OBJ)
	$(RM) *.dSYM
	make clean -C libft
fclean: clean
	$(RM) $(VM)
	$(RM) $(ASM)
	make fclean -C libft
re: fclean all
