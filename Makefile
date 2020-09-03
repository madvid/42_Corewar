# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 16:48:33 by mdavid            #+#    #+#              #
#    Updated: 2020/09/04 13:06:47 by mdavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM = corewar
VM_VISU = corewar_visu
ASM = asm
DASM = dasm
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	OS = LINUX
endif
ifeq ($(UNAME_S),Darwin)
	OS = Darwin
endif

ifndef TMP
	TMP = 0
endif

INC_DIR = include/
OP_H = $(INC_DIR)op.h
INC_VM = $(INC_DIR)vm.h $(INC_DIR)error_messages.h $(OP_H)
INC_ASM = $(INC_DIR)asm.h $(OP_H)
INC_DASM = $(INC_DIR)dasm.h $(OP_H)

LIBFT_DIR = libft
LIB_NAME = libft.a
LIB = -L $(LIBFT_DIR) -lft
LIBFT = $(LIBFT_DIR)/$(LIB_NAME)

SRC_DIR = srcs/
VM_DIR = vm/
ASM_DIR = asm/
DSM_DIR = dasm/
CM_DIR = commun/
ODIR = objects/
TMP_DIR = temp_tools/

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

CC = clang
FLAGS = -Wall -Wextra -Werror -Wunused-function -g -I$(INC_DIR)# -fsanitize=address -fstack-protector -fsanitize=undefined
RM = rm -rf

### SOURCES AND OBJECTS VARIABLES: ###

VM_FILES =	vm_parsing				\
			vm_parsing_init			\
			vm_parsing_champ_code	\
			vm_error_manager		\
			vm_tools_parsing		\
			vm_tools_champion_1		\
			vm_tools_champion_2		\
			vm_tools_get_champ		\
			vm_tools_encode_byte	\
			vm_tools_opcode			\
			vm_tools_process		\
			vm_tools_process2		\
			vm_tools_options		\
			vm_tools_op_functions	\
			vm_op_functions_1		\
			vm_op_functions_2		\
			vm_op_functions_3		\
			vm_op_functions_4		\
			vm_cw_arena_init		\
			vm_execution			\
			vm_tools_execution		\
			ft_lst_fdel_champ		\
			ft_lst_fdel_proc		\
			verbosity				\
			verbosity_fct			\
			verbo_tools

VS_FILES =	visu_arena				\
			visu_process			\
			visu_render				\
			visu_chp				\
			visu_menu				\
			visu_launch				\
			visu_players			\
			visu_tools				\
			visu_tools2				\
			ft_itoa_base2			\
			main_visu

ASM_FILES =	asm_main				\
			asm_get_cor				\
			asm_check_args			\
			asm_get_labels			\
			asm_tools

DSM_FILES =	dasm_main				\
			dasm_get_s

TMP_FILES = temporary_tools			\
			temporary_tools2		\
			temporary_tools3

ifeq ($(TMP),1)
	VM_FILES += $(TMP_FILES)
endif

VM_SRC = $(addprefix $(SRC_DIR)$(VM_DIR), $(addsuffix .c,$(VM_FILES)))
VM_SRC_VISU = $(addprefix $(SRC_DIR)$(VM_DIR), $(addsuffix .c,$(VS_FILES)))
AS_SRC = $(addprefix $(SRC_DIR)$(ASM_DIR), $(addsuffix .c,$(ASM_FILES)))
DS_SRC = $(addprefix $(SRC_DIR)$(DSM_DIR), $(addsuffix .c,$(DSM_FILES)))
OP_SRC = $(SRC_DIR)$(CM_DIR)op.c
MAIN_SRC = $(SRC_DIR)$(VM_DIR)main.c


VM_OBJ = $(patsubst %.c, $(ODIR)%.o, $(addsuffix .c,$(VM_FILES)))
VM_OBJ_VISU = $(patsubst %.c, $(ODIR)%.o, $(addsuffix .c,$(VS_FILES)))
AS_OBJ = $(patsubst %.c, $(ODIR)%.o, $(addsuffix .c,$(ASM_FILES)))
DS_OBJ = $(patsubst %.c, $(ODIR)%.o, $(addsuffix .c,$(DSM_FILES)))
OP_OBJ = $(ODIR)op.o
MAIN_OBJ = $(ODIR)main.o

vpath %.c $(SRC_DIR)vm
vpath %.c $(SRC_DIR)asm
vpath %.c $(SRC_DIR)dsm
vpath %.c $(SRC_DIR)commun
vpath %.c $(SRC_DIR)temp_tools # TEMPORAIRE !!!!!!!!!
vpath %.o $(ODIR)
vpath %.h $(INC_DIR)

VM_D = $(VM_SRC:.c=.d)# temporaire !!!!
DEP_NAME = $(VM_FILES:.c=.o)

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

### RULES: ###i

all: $(ODIR) $(VM) $(VM_VISU) $(ASM) $(DASM)

$(VM): $(ODIR) $(LIBFT) $(MAIN_OBJ) $(OP_OBJ) $(VM_OBJ)
	@echo "$(VIOLET)[$(CC)] $(CYAN)Constructing executable:$(NOC) $@\n"
	@$(CC) $(FLAGS) -o $@ $(MAIN_OBJ) $(VM_OBJ) $(OP_OBJ) -I$(INC_DIR) $(LIB)

$(VM_VISU): $(ODIR) $(LIBFT) $(OP_OBJ) $(VM_OBJ) $(VM_OBJ_VISU)
	@echo "$(VIOLET)[$(CC)] $(CYAN)Constructing executable:$(NOC) $@\n"
	@$(CC) $(FLAGS) -o $@ $(VM_OBJ) $(VM_OBJ_VISU) $(OP_OBJ) -I$(INC_DIR) $(LIB) -F $(FW_PATH)\
		-framework SDL2\
		-framework SDL2_image\
		-framework SDL2_ttf\
		-framework SDL2_mixer
	@install_name_tool -change @rpath/$(SDL2) $(SDL2_PATH) $@
	@install_name_tool -change @rpath/$(SDL2_IMG) $(SDL2_IMG_PATH) $@
	@install_name_tool -change @rpath/$(SDL2_TTF) $(SDL2_TTF_PATH) $@
	@install_name_tool -change @rpath/$(SDL2_MXR) $(SDL2_MXR_PATH) $@
-include $(DEP)

$(ASM) : $(ODIR) $(LIBFT) $(OP_OBJ) $(AS_OBJ)
	@$(CC) $(FLAGS) -o $@ $(AS_OBJ) $(OP_OBJ) $(LIB)
	@echo "$(VIOLET)[$(CC)] $(CYAN)Constructing executable:$(NOC) $@\n"

$(DASM) : $(ODIR) $(LIBFT) $(OP_OBJ) $(DS_OBJ)
	@$(CC) $(FLAGS) -o $@ $(DS_OBJ) $(OP_OBJ) $(LIB)
	@echo "$(VIOLET)[$(CC)] $(CYAN)Constructing executable:$(NOC) $@\n"

$(VM_OBJ) : $(ODIR)%.o: %.c $(INC_VM) 
	@echo " $(VIOLET)[$(CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INC_DIR)

$(VM_OBJ_VISU) : $(ODIR)%.o: %.c $(INC_VM)
ifeq ($(OS),Darwin)
	@$(CC) $(FLAGS) -o $@ -MMD -MP -c $< -I$(INC_DIR) -F $(FW_PATH)
endif

$(MAIN_OBJ) : $(ODIR)%.o: %.c $(INC_VM)
	@echo " $(VIOLET)[$(CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INC_DIR)

$(AS_OBJ) : $(ODIR)%.o: %.c $(INC_ASM)
	@echo " $(VIOLET)[$(CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INC_DIR)

$(DS_OBJ) : $(ODIR)%.o: %.c $(INC_DASM)
	@echo " $(VIOLET)[$(CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INC_DIR)

$(OP_OBJ) : $(ODIR)%.o: %.c $(OP_H)
	@echo " $(VIOLET)[$(CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INC_DIR)

$(LIBFT): $(LIBFT_DIR)/$(INC_DIR)libft.h
	@make -sC $(LIBFT_DIR)

$(ODIR) :
	@echo "$(CYAN)Objects directory:$(NOC) $@"
	@mkdir $@

show:
	@echo "$(RED)CC, FLAGS and OS:$(NOC)"
	@echo " $(YELLOW)CC=$(NOC) $(CC)"
	@echo " $(YELLOW)FLAGS=$(NOC) $(FLAGS)"
	@echo " $(YELLOW)OS=$(NOC) $(OS)"
	@echo "\n$(RED)Binary targets:$(NOC)"
	@echo " $(YELLOW)VM=$(NOC) $(VM)  $(YELLOW)ASM=$(NOC) $(ASM)  $(YELLOW)DASM=$(NOC) $(DASM)"
	@echo "\n$(RED)Files, Sources and objects:$(NOC)"
	@echo " $(YELLOW)VM_FILES=$(NOC) $(VM_FILES)"
	@echo " $(YELLOW)VM_SRC=$(NOC) $(VM_SRC)"
	@echo " $(YELLOW)VM_OBJ=$(NOC) $(VM_OBJ)\n"
	@echo " $(YELLOW)ASM_FILES=$(NOC) $(ASM_FILES)"
	@echo " $(YELLOW)ASM_SRC=$(NOC) $(AS_SRC)"
	@echo " $(YELLOW)ASM_OBJ=$(NOC) $(AS_OBJ)\n"
	@echo " $(YELLOW)DSM_FILES=$(NOC) $(DSM_FILES)"
	@echo " $(YELLOW)DSM_SRC=$(NOC) $(DS_SRC)"
	@echo " $(YELLOW)DSM_OBJ=$(NOC) $(DS_OBJ)\n"
	@echo "\n$(RED)header files:$(NOC)"
	@echo " $(YELLOW)INC_VM=$(NOC) $(INC_VM)"
	@echo " $(YELLOW)INC_ASM=$(NOC) $(INC_ASM)"
	@echo " $(YELLOW)INC_DASM=$(NOC) $(INC_DASM)"

norm:
	@echo "\n $(VIOLET)[norminette]$(NOC) $(CYAN)Checking norm of:$(NOC) $(LIBFT_DIR)/$(SRC_DIR) and header files"
	@norminette $(LIBFT_DIR)/$(SRC_DIR) $(LIBFT_DIR)/
	@echo "\n $(VIOLET)[norminette]$(NOC) $(CYAN)Checking norm of:$(NOC) $(VM) and $(INC_VM)"
	@norminette $(SRC_DIR)$(VM_DIR) $(INC_VM)
	@echo "\n $(VIOLET)[norminette]$(NOC) $(CYAN)Checking norm of:$(NOC) $(ASM) and $(INC_ASM)"
	@norminette $(SRC_DIR)$(ASM_DIR) $(INC_ASM)
	@echo "\n $(VIOLET)[norminette]$(NOC) $(CYAN)Checking norm of:$(NOC) $(DSM) and $(INC_DSM)"
	@norminette $(SRC_DIR)$(DSM_DIR) $(INC_DSM)

FORCE:

clean:
	@echo "\n $(CYAN)Supressing libft objects$(NOC)..."
	@make clean -C $(LIBFT_DIR)
	@echo " $(RED)-> libft objects destroyed$(NOC)"
	@echo "\n $(CYAN)Supressing corewar objects$(NOC)..."
	@rm -rf $(ODIR)
	@echo " $(RED)-> corewar objects destroyed$(NOC)"
	@echo "\n $(CYAN)Supressing $(VM) files with .d extension [THIS IS TEMPORARY]$(NOC)..."
	@rm -rf $(VM_D)
	@echo " $(RED)-> $(VM) .d files destroyed$(NOC)"

fclean: clean
	@echo "\n $(CYAN)Supressing libft static library$(NOC)..."
	@make fclean -C $(LIBFT_DIR)
	@echo " $(RED)-> static library destroyed$(NOC)"
	@echo " \n$(CYAN)Supressing executables$(NOC)..."
	@rm -rf $(VM) $(ASM) $(DASM)
	@echo " $(RED)->$(VM) executable destroyed$(NOC)"

re : fclean all

.PHONY: all show norm FORCE clean fclean re
