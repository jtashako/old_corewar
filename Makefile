# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jochang <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/10 15:16:58 by jochang           #+#    #+#              #
#    Updated: 2019/03/11 12:36:56 by jochang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASSEMBLER = asm
COREWAR = corewar

PC = pc/pc_app.c \
	pc//pc_free.c \
	pc/pc_new.c \
	pc/pc_rem_head.c \
	pc/pc_rem.c \
	pc/pc_scan_rem.c \
	pc/pc_scan_op.c \

OP = op/op_add.c \
	op/op_aff.c \
	op/op_and.c \
	op/op_fork.c \
	op/op_ld.c \
	op/op_ldi.c \
	op/op_lfork.c \
	op/op_live.c \
	op/op_lld.c \
	op/op_lldi.c \
	op/op_or.c \
	op/op_st.c \
	op/op_sti.c \
	op/op_sub.c \
	op/op_xor.c \
	op/op_zjmp.c \

ASRC = assembler/arg.c \
	assembler/asm.c \
	assembler/assembler.c \
	assembler/get_bytecode.c \
	assembler/get_header.c \
	assembler/label.c \
	assembler/op.c \
	assembler/parser.c \
	assembler/t_byte.c \
	assembler/valid_extension.c \

CSRC = core_war/corewar.c \
	core_war/ft_setopt.c \
	core_war/parse_file.c \
	core_war/init_vm.c \
	core_war/op_fn.c \
	core_war/init_env.c \
	core_war/ft_memrcpy.c \
	core_war/ft_memfree.c \
	core_war/acb_len.c \
	core_war/display.c \
	core_war/mem_func.c \
	core_war/debug.c

AINC = -I inc/ \
	-Ilibft/. \

CINC = -I inc/ \
	-Ilibft/. \

ERR = err/err_invarg.c \
	err/err_invfile.c \
	err/err_invflag.c \
	err/err_invheader.c \
	err/err_invop.c \
	err/err_malloc.c \
	err/err_nofile.c \

GUI = gui/delete_gui.c \
	gui/init_gui.c \
	gui/print_breakdown.c \
	gui/update_gui.c \
	gui/update_infoblock.c \
	gui/update_memblock.c \
	gui/splash/debris.c \
	gui/splash/explosion.c \
	gui/splash/ft_prand.c \
	gui/splash/name.c \
	gui/splash/splash_screen.c \

GCC = gcc
CFLAGS = -Wall -Wextra -Werror
LFT = -L libft -lft
NCR = -lncurses
MATH = -lm

CORE = $(CSRC) $(ERR) $(PC) $(OP) $(GUI) $(CINC) $(LFT) $(NCR) $(MATH)
ASM = $(ASRC) $(ERR) $(AINC) $(LFT)

.PHONY: all clean fclean re lldb faddress

all: $(COREWAR)

$(COREWAR):
	@make --no-print-directory -C libft
	@echo "\033[32mmaking assembler...\033[0m"
	@$(GCC) $(CFLAGS) -o $(ASSEMBLER) $(ASM)
	@echo "\033[32mmaking corewar...\033[0m"
	@$(GCC) $(CFLAGS) -o $(COREWAR) $(CORE)

clean:
	@make --no-print-directory -C libft clean
	@echo "\033[33mcleaning repository...\033[0m"
	@rm -rf *.gch *~ \#*\# *.dSYM

fclean: clean
	@make --no-print-directory -C libft fclean
	@echo "\033[33mremoving executables...\033[0m"
	@rm -f $(ASSEMBLER)
	@rm -f $(COREWAR)

re: fclean all

lldb:
	@make --no-print-directory -C libft
	@echo "\033[32mmaking lldb executables...\033[0m"
	@$(GCC) $(CFLAGS) -o $(ASSEMBLER) $(ASM) -g
	@$(GCC) $(CFLAGS) -o $(COREWAR) $(CORE) -g

faddress:
	@make fsan -C libft
	@echo "\033[32mmaking address sanitizer executables...\033[0m"
	@$(GCC) $(CFLAGS) -o $(ASSEMBLER) $(ASM) -g -fsanitize=address
	@$(GCC) $(CFLAGS) -o $(COREWAR) $(CORE) -g -fsanitize=address
