# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 16:48:33 by weilin            #+#    #+#              #
#    Updated: 2020/07/09 13:04:07 by mdavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM = vm

INCLUDE = vm.h
SRC_DIR = srcs/
VM_DIR = vm/
INC_DIR = include/
LIB_DIR = libraries/
LIBFT_DIR = libft
LIB_NAME = libft.a
LIB = -L $(LIB_DIR) -lft
LIBFT = $(LIBFT_DIR)/$(LIB_NAME)

CC = gcc
FLAGS = -Wall -Wextra -Werror -Wunused-function -g -I$(INC_DIR) #-fsanitize=address -fstack-protector -fsanitize=undefined
RM = rm -rf

### SOURCES AND OBJECTS VARIABLES: ###

VM_FILES =	main \
			vm_parsing \
			vm_error_managers

VM_SRC = $(addprefix $(SRC_DIR)$(VM_DIR), $(addsuffix .c,$(VM_FILES)))
VM_OBJ = $(VM_SRC:.c=.o)

### COLORS ###

NOC = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
VIOLET = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m

### RULES: ###

all: $(VM)

$(VM): $(VM_OBJ)
	@echo "\n $(VIOLET)[$(CC)] $(CYAN)Constructing executable:$(NOC) $@"
	@$(CC) $(FLAGS) -o $@ $(VM_OBJ) $(LIB)

$(VM_OBJ): $(INC_DIR)/vm.h $(LIBFT)

%.o: %.c
	@echo " $(VIOLET)[$(CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(LIBFT_DIR)/$(INC_DIR)

$(LIBFT): $(LIBFT_DIR)/$(INC_DIR)libft.h
	@make -sC $(LIBFT_DIR)

show:
	@echo " $(YELLOW)VM_FILES=$(NOC) $(VM_FILES)\n"
	@echo " $(YELLOW)VM_SRC=$(NOC) $(VM_SRC)\n"
	@echo " $(YELLOW)VM_OBJ=$(NOC) $(VM_OBJ)\n"

norm:
	@echo "\n $(VIOLET)[norminette]$(NOC) $(CYAN)Checking norm of:$(NOC) $(VM) $(LIBFT)"
	@norminette $(SRC_DIR)$(VM) $(INC_DIR) $(LIBFT_DIR)/$(SRC_DIR) | grep -v Norme -B1 || echo "$(VIOLET)[norm] vm and libft: $(GREEN)All clear$(NOC)"

clean:
	@make clean -C $(LIBFT_DIR)
	@echo "\n $(CYAN)Supressing $(VM) objects$(NOC)..."
	@rm -rf $(VM_OBJ)
	@echo " $(RED)-> $(VM) objects destroyed$(NOC)"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@echo " \n$(CYAN)Supressing $(PS) $(CHK) executables and repository libraries$(NOC)..."
	@rm -rf $(VM)
	@echo " $(RED)->$(VM) executable destroyed$(NOC)"
	@rm -rf $(LIB_DIR)
	@echo " $(RED)->$(LIB_DIR) repository destroyed$(NOC)"

re : fclean all

.PHONY: all show norm clean fclean re
