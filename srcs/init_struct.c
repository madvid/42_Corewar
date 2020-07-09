/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:30:11 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/09 13:38:50 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

t_code    *ft_create_elem(void)
{
    t_code *elem;
    
	if (!(elem = malloc(sizeof(t_code))))
		return (NULL);
    if (!(elem->label = (char*)malloc(sizeof(char) * 10)))
        return (NULL);
    if (!(elem->op = (char*)malloc(sizeof(char) * 10)))
        return (NULL);
    if (!(elem->enc_byte = (char*)malloc(sizeof(char) * 11)))
        return (NULL);
    elem->len = 2;
    elem->position = 0;
    elem->next = NULL;
	return (elem);
}

void    init_head(t_head *head)
{   
    if (!(head->name = (char*)malloc(sizeof(char) * PROG_NAME_LENGTH)))
        return ;
    if (!(head->comment = (char*)malloc(sizeof(char) * COMMENT_LENGTH)))
        return ;
    head->magic = COREWAR_EXEC_MAGIC;
	head->op_code = NULL;
}
