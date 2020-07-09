/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 09:56:07 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/09 10:01:04 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

t_code    *create_nod(t_head *head, t_code *tmp)
{
    if (tmp == NULL)
    {
        if (!(head->op_code = ft_create_elem()))
		    return NULL;
        tmp = head->op_code;
    }
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        if (!(tmp->next = ft_create_elem()))
		    return NULL;
        tmp = tmp->next;
    }
    return (tmp);
}

void    print_op_code(t_head *head)
{
    t_code *tmp;
    int i;

    tmp = head->op_code;
    while (tmp)
    {
        ft_printf(YELLOW"label = %s\n"EOC, tmp->label);
        ft_printf(PURPLE"op = %s\n"EOC, tmp->op);
        i = 0;
        while (tmp->arg[i])
        {
            printf(CYAN"arg[%d] = %s\n"EOC, i, tmp->arg[i]);
            i++;
        }
        i = 0;
        while (tmp->hexa_arg[i])
        {
            ft_printf(GREEN"Hexa[%d] = %s\n"EOC, i, tmp->hexa_arg[i]);
            i++;
        }
        tmp = tmp->next;
    }
}