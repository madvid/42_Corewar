# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaye <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/03 12:52:52 by yaye              #+#    #+#              #
#    Updated: 2020/02/26 16:14:54 by yaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC	 = clang
CFLAGS = -Wall -Wextra -Werror
#CFLAGS += -fsanitize=address,undefined -g3
INCL = -Iincludes

SRCS = ft_abs.c ft_atoi.c ft_atoi_base.c ft_bzero.c ft_hexatod.c ft_isalnum.c \
ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c \
ft_lstaddbel.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
ft_lstlst.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_power.c \
ft_printbits.c ft_printf.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c \
ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c \
ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c \
ft_strsplit_lst.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
ft_toupper.c get_next_line.c parse.c parse_b.c parse_c.c parse_di.c parse_f.c \
parse_o.c parse_p.c parse_s.c parse_u.c parse_x.c parse_xcap.c ft_igap.c \
ft_min.c ft_max.c ft_ascendingsort.c ft_isblanc.c ft_log2.c ft_stoi.c
ODIR = ./objects/
OBJS = $(patsubst %.c, $(ODIR)%.o, $(SRCS))
HEAD = includes/libft.h

vpath %.c ./sources/

all : $(NAME)

$(NAME) : $(ODIR) $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "\033[1;32m%35s	COMPILED\033[0m\n" "$(NAME)"

$(OBJS): $(ODIR)%.o: %.c $(HEAD)
	@$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf "\033[32m%35s	COMPILED\033[0m\n" "libft/$@" 

$(ODIR):
	@mkdir $@

clean :
	@$(RM) $(OBJS)
	@$(RM) -R $(ODIR)
	@printf "\033[31m%35s	REMOVED\033[0m\n" ".o"

fclean : clean
	@$(RM) $(NAME)
	@printf "\033[31m%35s	REMOVED\033[0m\n" "$(NAME)"

re : fclean
	@$(MAKE)

#.SILENT :
.PHONY: all clean fclean re
