/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:30:11 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/07 16:06:47 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

void    init_head(t_head *head)
{
    if (!(head->name = (char*)malloc(sizeof(char) * PROG_NAME_LENGTH)))
        return ;
    if (!(head->comment = (char*)malloc(sizeof(char) * COMMENT_LENGTH)))
        return ;
    head->magic = COREWAR_EXEC_MAGIC;
}

void    init_code(t_code *code)
{
    int i;

    if (!(code->label = (char*)malloc(sizeof(char) * 10)))
        return ;
    if (!(code->instruction = (char*)malloc(sizeof(char) * 10)))
        return ;
    i = 0;
    while (i < 4)
    {
        code->indirect_type[i] = 0;
        code->direct_type[i] = 0;
        i++;
    }
    code->reg = 0;
    code->arg = 0;
}

t_label     *ft_create_elem(t_label *elem)
{
	if (!(elem = malloc(sizeof(t_label))))
		return (NULL);
	if (elem)
	{
        elem->name = "\0";
        elem->value = 0;
		elem->next = NULL;
	}
	return (elem);
}

t_label     init_label(t_label *label)
{
    label->first = NULL;
	label->next = NULL;
	label->name = "\0";
    label->value = 0;
    return (*label);
}
