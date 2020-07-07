# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: armajchr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/14 12:01:40 by armajchr          #+#    #+#              #
#    Updated: 2019/10/01 15:29:27 by armajchr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Binaries
CC		= /usr/bin/gcc
AR 		= /usr/bin/ar
RANLIB	= /usr/bin/ranlib
RM		= /bin/rm

NAME = libftprintf.a
FLAG = -Wall -Wextra -Werror
SRC = ft_printf.c	\
	  buffer.c		\
	  type_char.c	\
	  type_point.c	\
	  type_point2.c	\
	  type_point3.c	\
	  type_str.c	\
	  type_u.c		\
	  type_u2.c		\
	  type_hexa.c	\
	  type_hexa2.c	\
	  type_hexa_cap.c	\
	  type_hexa_cap2.c	\
	  type_octal.c	\
	  type_octal2.c	\
	  type_bin.c	\
	  type_int.c	\
	  type_int2.c	\
	  type_int3.c	\
	  type_undefined.c	\
	  type_float.c	\
	  type_float2.c	\
	  type_float3.c	\
	  ft_strcmp.c	\
	  ft_strnew.c	\
	  ft_bzero.c	\
	  ft_atoi.c		\
	  ft_itoa.c		\
	  ft_strchrf.c	\
	  ft_strlen.c	\
	  ft_putstr.c	\
	  parsing.c		\
	  parsing2.c	\
	  ft_unsigned_itoa.c	\
	  ft_itoa_base2.c		\
	  ft_isprint.c	\
	  ft_isdigit.c	\
	  ft_itoa_float.c	\
	  ft_strcat.c	\
	  ft_strjoin.c	\

OBJ	= $(patsubst %.c,%.o,$(SRC))
HFILES = ft_printf.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HFILES) Makefile $(SRC)
		@echo "\033[0;33mBuilding $(NAME) ...\033[0m"
		@$(AR) rc $(NAME) $(OBJ)
		@$(RANLIB) $(NAME)
		@echo "\033[0;35mThe library $(NAME) is ready to print your shit\033[0m"

%.o:		%.c
		@echo "\033[0;32m[OK] \033[0m	\033[0;33m Compiling:\033[0m" $@
		@$(CC) $(CFLAGS) -c $< -o $@ -I.

clean:
		@$(RM) -f $(OBJ)

fclean: clean
		@$(RM) -f $(NAME)

re: fclean all
