/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:16:00 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/07 16:09:02 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/asm.h"

void    get_label_code(t_code *code, t_label *label, char *line)
{
    t_label *tmp;

    if (!(tmp = ft_create_elem(label)))
		return ;
    line = line + 1;
    tmp->next = label->first;
    label->first = tmp;
    tmp->name = code->label;
    tmp->value = ft_atoi(tmp->name);
    ft_printf("value = %p\n", tmp->value);
}

void    parse_instruction(t_code *code, t_label *label, char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if ((line[i] == ':') && (line[i - 1] != '%'))
        {
            code->label = ft_strncpy(code->label, line, i);
            get_label_code(code, label ,line);
        }
        i++;
    }
}