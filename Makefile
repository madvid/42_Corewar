# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 14:17:47 by armajchr          #+#    #+#              #
#    Updated: 2020/07/08 11:51:59 by armajchr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

#Binaries
#CC		= /usr/bin/gcc -g -fsanitize=address
CC		= /usr/bin/gcc

RM		= /bin/rm
FLAGS	= -Wall -Wextra -Werror
FLAGS += -fsanitize=address,undefined -g3

NAME	= asm_test
LIB1	= Libft/libft.a
LIB2	= ft_printf/libftprintf.a

HEADER	= incs/asm.h
INCLUDE = incs/

SRC		= parsing.c			\
		parsing_head.c		\
		parsing_code.c		\
		init_struct.c		\
		error_handler.c		\
		ft_atoi.c			\
		tools.c				\

OBJ_PATH = obj
OBJ_NAME = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

DEP_NAME = $(SRC_NAME:.c=.d)

.PHONY: all clean fclean re

all: mkdir $(NAME)

mkdir: 
	@mkdir -p $(OBJ_PATH)
	
$(NAME): $(LIB1) $(LIB2) $(OBJ) $(HEADER) Makefile
	clang -g3 $(FLAGS) -o $(NAME) $(OBJ) $(LIB1) $(LIB2) -I $(INCLUDE)
	@echo "$(YELLOW)./$(NAME)     $(GREEN)ready   ✅ $(RESET)"

-include $(DEP)

$(OBJ_PATH)/%.o : ./srcs/%.c $(INCLUDE) $(HEADER)
	gcc -g3 $(FLAGS) -I Libft -I ft_printf -I ./incs -MMD -MP -c $< -o $@

$(LIB1): $(LIB2) force
	make -C Libft

$(LIB2): force
	make -C ft_printf

force:
	@true

clean:
	@rm -f $(OBJ)
	@echo "$(YELLOW).o        $(RED)deleted 💯 $(RESET)"
	@rm -f $(DEP)
	@echo "$(YELLOW).d        $(RED)deleted 💯 $(RESET)"
	@rm -rf $(OBJ_PATH)
	@make -C Libft clean
	@make -C ft_printf clean

fclean: clean
	@make -C Libft fclean
	@make -C ft_printf fclean
	@$(RM) -f $(NAME)
	@echo "$(YELLOW)./$(NAME)     $(RED)deleted 💯 $(RESET)"

re: fclean all
