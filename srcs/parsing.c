/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 10:18:52 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/10 11:28:15 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

void    parse_instruction(t_head *h, char *line)
{
    int i;
    t_code  *tmp;

    tmp = h->op_code;
    i = 0;
    ft_printf("line = %s\n", line);
    if (line[0])
        tmp = create_nod(head, tmp);
    if (ft_strchr(line, ':'))
    {
        tmp = is_label(tmp, line);
        if (tmp->label)
            i = ft_strlen(tmp->label) + 1;
    }
    else
    {
        tmp->label = NULL;
        i = 0;
    }
    get_op_code_info(tmp, line, i);
}

void    parse(t_head *h, int i)
{
    while (h->buff[i])
    {
        if ((h->buff[i] == '#') || (h == '\0'))
            i++;;
        else if (line[0] == '.')
            ft_is_name(head, line);
        else
            parse_instruction(head, line);
    }
}
