/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:17:00 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/09 10:03:54 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

void    arg_to_hexa(t_head *head)
{
    t_code *tmp;
    int i;

    i = 0;
    tmp = head->op_code;
    while (tmp)
    {
        printf("tmp = %s\n", tmp->op);
        while (tmp->arg[i])
        {
            ft_printf("arg = %s\n", tmp->arg[i]);
            if (tmp->arg[i][0] == 'r')
            {
                if (!(tmp->hexa_arg[i] = (char*)malloc(sizeof(char) * 8)))
                    return ;
                tmp->hexa_arg[i] = "r0\0";
            }
            else if (tmp->arg[i][0] == '%')
            {
                if (!(tmp->hexa_arg[i] = (char*)malloc(sizeof(char) * 8)))
                    return ;
                tmp->hexa_arg[i] = "00 00 00 00\0";
            }
            else
            {
                if (!(tmp->hexa_arg[i] = (char*)malloc(sizeof(char) * 8)))
                    return ;
                tmp->hexa_arg[i] = "00 00\0";
            }
            i++;
            ft_printf("i = %d\n", i);
            ft_printf("hexa = %s\n", tmp->hexa_arg[i]);
        }
        i = 0;
        tmp = tmp->next;
    }
}