# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaye <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 11:17:35 by yaye              #+#    #+#              #
#    Updated: 2019/11/28 11:17:37 by yaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM  = asm
DASM = dasm
CC	 = clang
CFLAGS = -Wall -Wextra -Werror -Wpadded
CFLAGS += -fsanitize=address,undefined -g3
INCL = -Iincludes -Ilibft/includes

LBFT = libft/libft.a

AS_S = asm_main.c asm_get_cor.c asm_check_args.c asm_get_labels.c asm_tools.c \
	   op.c
DS_S = dasm_main.c dasm_get_s.c op.c
ODIR = ./objects/
AS_O = $(patsubst %.c, $(ODIR)%.o, $(AS_S))
DS_O = $(patsubst %.c, $(ODIR)%.o, $(DS_S))

AS_H = includes/asm.h includes/op.h
DS_H = includes/dasm.h includes/op.h

vpath %.c ./sources/

all : $(ODIR) $(ASM) $(DASM)

$(ASM) : $(LBFT) $(AS_O)
	$(CC) $(CFLAGS) -o $@ $(AS_O) $(INCL) -Llibft/ -lft
	@printf "\033[1;32m%35s	COMPILED\033[0m\n" "$(ASM)"

$(DASM) : $(LBFT) $(DS_O)
	$(CC) $(CFLAGS) -o $@ $(DS_O) $(INCL) -Llibft/ -lft
	@printf "\033[1;32m%35s	COMPILED\033[0m\n" "$(DASM)"

$(LBFT) : FORCE
	@$(MAKE) -C libft

$(AS_O) : $(ODIR)%.o: %.c $(AS_H)
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf "\033[32m%35s	COMPILED\033[0m\n" "$@"

$(DS_O) : $(ODIR)%.o: %.c $(DS_H)
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf "\033[32m%35s	COMPILED\033[0m\n" "$@"

$(ODIR) :
	mkdir $@

FORCE :

clean :
	$(RM) $(AS_O)
	$(RM) $(DS_O)
	$(RM) $(ARG)
	$(RM) -R $(ODIR)
	$(MAKE) clean -C libft

fclean : clean
	$(RM) $(ASM)
	@printf "\033[31m%35s	REMOVED\033[0m\n" "$(ASM)"
	$(RM) $(DASM)
	@printf "\033[31m%35s	REMOVED\033[0m\n" "$(DASM)"
	$(RM) $(LBFT)
	@printf "\033[31m%35s	REMOVED\033[0m\n" "$(LBFT)"

re : fclean
	@$(MAKE)

#.SILENT:
.PHONY: all FORCE clean fclean re
