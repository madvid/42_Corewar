# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 16:48:33 by weilin            #+#    #+#              #
#    Updated: 2020/08/04 10:09:32 by mdavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIB_DIR = libft/
LIB_FILES = ft_atoi			\
			ft_strlen		\
			ft_bzero		\
			ft_isdigit		\
			ft_strchr		\
			ft_int_len		\
			ft_strdup		\
			ft_strsub		\
			ft_strtolower	\
			ft_strjoin		\
			ft_strnew		\
			ft_strcat		\
			ft_strcpy		\
			ft_itoa			\
			ft_strnew_c		\
			ft_strdel		\
			ft_memalloc		\
			ft_memdel		\
			ft_strcmp		\
			ft_strreset 

FILES =	ft_printf	\
		parse		\
		tool		\
		type_csp	\
		print_chars	\
		print_addr	\
		type_di		\
		base		\
		type_ox		\
		print_int	\
		type_uint	\
		parse_flags

FILES+= $(addprefix $(LIB_DIR),$(LIB_FILES))

CC = gcc
FLAG = -Wall -Wextra -Werror -g -I $(INC_DIR)

RM = rm -rf

CCH_DIR = cache/
SRC_DIR = src/
INC_DIR = include/

SRC = $(addprefix $(SRC_DIR),$(addsuffix .c,$(FILES)))
OBJ = $(addprefix $(CCH_DIR),$(addsuffix .o,$(FILES)))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^
# Running "ar s" on an archive is equivalent to running ranlib on it.
# $^ means the all prerequisites

$(CCH_DIR)%.o: $(SRC_DIR)%.c | $(CCH_DIR)
	$(CC) $(FLAG) -c $< -o $@
#if .o is older than .c, then do the content
# $< means the first prerequisite
# | The names of all the order-only prerequisites, with spaces between them.

$(CCH_DIR):
	mkdir $@
	mkdir $(CCH_DIR)$(LIB_DIR)

clean:
	$(RM) $(CCH_DIR)
	$(RM) *.o
	$(RM) *.out*

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

norm:
	norminette $(SRC) $(INC_DIR) | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm
