/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:21:30 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/09 16:31:48 by armajchr         ###   ########.fr       */
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
    struct s_code   *op_code;
}                   t_head;

typedef struct      s_code
{
    char            *label;
    char            *op;
    char            *enc_byte;
    char            *arg[4];
    char            *hexa_arg[6];
    int             len;
    int             position;
    struct s_code   *next;
}                   t_code;

/**Lexical parsing**/

/**Tools**/
t_code     *ft_create_elem(void);
long long	ft_atoi(const char *str);
t_code      *create_nod(t_head *head, t_code *tmp);
void        print_op_code(t_head *head);
char      *padding(char *s, int size);

/**Launch**/
void        init_head(t_head *head);

/**parsing_head**/
void        parse(t_head *head, int fd);
void        ft_is_name(t_head *head, char *line);
void        ft_get_comment(t_head *head, char *line);
void        ft_get_name(t_head *head, char *line);

/**parsing_code**/
void        parse_instruction(t_head *head, char *line);
void        get_op_code_info(t_code *tmp, char *line, int i);
t_code      *is_label(t_code *tmp, char *line);
void        dispatch_info(t_code *tmp, char **s, int argu);

/**hexa_args**/
void        arg_to_hexa(t_head *head);
void        instruction_to_hexa(t_head *head);
void    get_direct(t_code *tmp, int i);

/**Errors**/
int         ft_error_arg(void);

#endif
