/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:21:30 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/10 13:24:30 by armajchr         ###   ########.fr       */
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
    int             fd;
    char            buff[MEM_SIZE + 3];
    int             i;
    char            *header; //name comment magic 
    char            *hexa_header; //same in hexa
    struct s_code   *op_code;
}                   t_head;

typedef struct      s_code
{
    char            *label; //malloc
    char            *instruction; //op + encoded + args (line)
    char            *hexa_instruction; //"op" "encoded" "args" (hexa_line)
    int             len;
    int             position;
    struct s_code   *next;
}                   t_code;

/**Lexical parsing**/

/**Init**/
t_code              *ft_create_elem(void);
long long           ft_atoi(const char *str);
t_code              *create_nod(t_head *h, t_code *tmp);
void                print_op_code(t_head *h);
char                *padding(char *s, int size);
void                release(t_head *h);
void                leave(t_head *h, char *s);

/**Scout**/
int     is_white(char c);
int     is_head(char *s);
int     is_com(t_head *h, char c);
int     is_label(char *s, int i);


/**Launch**/
void        init_head(t_head *h, char *av);

/**parsing_head**/
void        parse(t_head *h, int fd);
void        ft_is_name(t_head *h, char *line);
void        ft_get_comment(t_head *h, char *line);
void        ft_get_name(t_head *h, char *line);

/**parsing_code**/
void        parse_instruction(t_head *h, char *line);
void        get_op_code_info(t_code *tmp, char *line, int i);
t_code      *is_label(t_code *tmp, char *line);
void        dispatch_info(t_code *tmp, char **s, int argu);

/**hexa_args**/
void        arg_to_hexa(t_head *h);
void        instruction_to_hexa(t_head *h);
void    get_direct(t_code *tmp, int i);

/**Errors**/
int         ft_error_arg(void);

#endif
