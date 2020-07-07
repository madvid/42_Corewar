/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:21:30 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/07 16:05:16 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "../Libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../Libft/get_next_line.h"
# include "op.h"

typedef struct      s_head
{
    char            *name;
    char            *comment;
    unsigned int    magic;
}                   t_head;

typedef struct      s_code
{
    char            *label;
    char            *instruction;
    unsigned int    indirect_type[4];
    unsigned int    direct_type[4];
    unsigned int    reg;
    int             arg;
}                   t_code;

typedef struct     s_label
{
    struct s_label  *first;
    struct s_label  *next;
    char            *name;
    unsigned int    value;
}                   t_label;



/**Lexical parsing**/

/**Tools**/
t_label     *ft_create_elem(t_label *elem);
long long	ft_atoi(const char *str);

/**Launch**/
void        init_head(t_head *head);
void        init_code(t_code *code);
t_label     init_label(t_label *label);

/**parsing_head**/
void        parse(t_head *head, t_code *code, t_label *label, int fd);
void        ft_is_name(t_head *head, char *line);
void        ft_get_comment(t_head *head, char *line);
void        ft_get_name(t_head *head, char *line);

/**parsing_code**/
void        parse_instruction(t_code *code, t_label *label, char *line);
void        get_label_code(t_code *code, t_label *label, char *line);
/**Errors**/
int         ft_error_arg(void);

#endif
