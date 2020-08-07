# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 16:48:33 by weilin            #+#    #+#              #
#    Updated: 2020/08/07 09:53:05 by mdavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM = vm

INCLUDE = vm.h error_messages.h
SRC_DIR = srcs/
VM_DIR = vm/
INC_DIR = include/
LIB_DIR = libraries/
LIBFT_DIR = libft
LIB_NAME = libft.a
LIB = -L $(LIBFT_DIR) -lft
LIBFT = $(LIBFT_DIR)/$(LIB_NAME)

#SDL
FW_PATH = ./visu/frameworks
SDL2 = SDL2.framework/Versions/A/SDL2
SDL2_IMG = SDL2_image.framework/Versions/A/SDL2_image
SDL2_TTF = SDL2_ttf.framework/Versions/A/SDL2_ttf
SDL2_MXR = SDL2_mixer.framework/Versions/A/SDL2_mixer
SDL2_PATH = $(FW_PATH)/$(SDL2)
SDL2_IMG_PATH = $(FW_PATH)/$(SDL2_IMG)
SDL2_TTF_PATH = $(FW_PATH)/$(SDL2_TTF)
SDL2_MXR_PATH = $(FW_PATH)/$(SDL2_MXR)

CC = gcc
FLAGS = -Wall -Wextra -Werror -Wunused-function -g -I$(INC_DIR) #-fsanitize=address -fstack-protector -fsanitize=undefined
RM = rm -rf

### SOURCES AND OBJECTS VARIABLES: ###

VM_FILES =	main					\
			op						\
			vm_parsing				\
			vm_parsing_init			\
			vm_parsing_champ_code	\
			vm_error_manager		\
			vm_tools_parsing		\
			vm_tools_champion		\
			vm_tools_get_champ		\
			vm_tools_encode_byte	\
			vm_tools_opcode			\
			vm_tools_process		\
			vm_tools_options		\
			vm_tools_op_functions	\
			vm_op_functions_1		\
			vm_op_functions_2		\
			vm_op_functions_3		\
			vm_op_functions_4		\
			vm_cw_arena_init		\
			vm_execution			\
			ft_lst_fdel_champ		\
			verbosity				\
			verbosity_fct			\
			ft_itoa_base2			\
			visu_arena				\
			visu_process			\
			visu_render				\
			visu_chp				\
			visu_menu				\
			visu_launch				\
			visu_tools				\
			temporary_tools

VM_SRC = $(addprefix $(SRC_DIR)$(VM_DIR), $(addsuffix .c,$(VM_FILES)))
VM_OBJ = $(VM_SRC:.c=.o)
VM_D = $(VM_SRC:.c=.d) # temporaire !!!!
 DEP_NAME = $(VM_FILES:.c=.o)
vpath %.c $(SRC_DIR)$(VM)
vpath %.c $(SRC_DIR)temp_tools
vpath %.o $(SRC_DIR)$(VM)
vpath %.h $(INC_DIR)

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

# $(VM): $(VM_OBJ)
# 	@$(CC) $(FLAGS) -o $@ $(VM_OBJ) $(LIB)
# 	@echo "\n $(VIOLET)[$(CC)] $(CYAN)Constructing executable:$(NOC) $@"

$(VM): $(VM_OBJ)
	@$(CC) $(FLAGS) -o $@ $(VM_OBJ) $(LIB) -F $(FW_PATH)\
		-framework SDL2\
		-framework SDL2_image\
		-framework SDL2_ttf\
		-framework SDL2_mixer
	@echo "\n $(VIOLET)[$(CC)] $(CYAN)Constructing executable:$(NOC) $@"
	@install_name_tool -change @rpath/$(SDL2) $(SDL2_PATH) $@
	@install_name_tool -change @rpath/$(SDL2_IMG) $(SDL2_IMG_PATH) $@
	@install_name_tool -change @rpath/$(SDL2_TTF) $(SDL2_TTF_PATH) $@
	@install_name_tool -change @rpath/$(SDL2_MXR) $(SDL2_MXR_PATH) $@
-include $(DEP)

$(VM_OBJ): $(INC_DIR)/vm.h $(LIBFT)

# $(SRC_DIR)$(VM_DIR)%.o: %.c
# 	@echo " $(VIOLET)[$(CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
# 	@$(CC) $(FLAGS) -o $@ -MMD -MP -c $< -I$(INC_DIR)
# 	@#$(CC) $(FLAGS) -o $@ -c $< -I$(INC_DIR)

$(SRC_DIR)$(VM_DIR)%.o: %.c
	@echo " $(VIOLET)[$(CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
	@$(CC) $(FLAGS) -o $@ -MMD -MP -c $< -I$(INC_DIR) -F $(FW_PATH)
	@#$(CC) $(FLAGS) -o $@ -c $< -I$(INC_DIR)

$(LIBFT): $(LIBFT_DIR)/$(INC_DIR)libft.h
	@make -sC $(LIBFT_DIR)

show:
	@echo " $(YELLOW)VM_FILES=$(NOC) $(VM_FILES)\n"
	@echo " $(YELLOW)VM_SRC=$(NOC) $(VM_SRC)\n"
	@echo " $(YELLOW)VM_OBJ=$(NOC) $(VM_OBJ)\n"

norm:
	@echo "\n $(VIOLET)[norminette]$(NOC) $(CYAN)Checking norm of:$(NOC) $(VM) $(LIBFT)"
	@norminette $(SRC_DIR)$(VM) $(INC_DIR) $(LIBFT_DIR)/$(SRC_DIR) | grep _visu Norme -B1 || echo "$(VIOLET)[norm] vm and libft: $(GREEN)All clear$(NOC)"

clean:
	@make clean -C $(LIBFT_DIR)
	@echo "\n $(CYAN)Supressing $(VM) objects$(NOC)..."
	@rm -rf $(VM_OBJ)
	@echo " $(RED)-> $(VM) objects destroyed$(NOC)"
	@echo "\n $(CYAN)Supressing $(VM) files with .d extension [THIS IS TEMPORARY]$(NOC)..."
	@rm -rf $(VM_D)
	@echo " $(RED)-> $(VM) .d files destroyed$(NOC)"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@echo " \n$(CYAN)Supressing $(PS) $(CHK) executables and repository libraries$(NOC)..."
	@rm -rf $(VM)
	@echo " $(RED)->$(VM) executable destroyed$(NOC)"
	@rm -rf $(LIB_DIR)
	@echo " $(RED)->$(LIB_DIR) repository destroyed$(NOC)"
	@echo "$(YELLOW)./$(NAME)     $(RED)deleted 💯 $(RESET)"

re : fclean all

.PHONY: all show norm clean fclean re
