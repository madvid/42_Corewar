/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:17:00 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/09 16:34:00 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

void    get_direct(t_code *tmp, int i)
{
    char    *str;
    int     len;
    
    str = tmp->arg[i];
    str = str + 1;
    if (str[0] == ':')
        return;
    ft_printf("hello\n");
    tmp->hexa_arg[i + 2] = ft_itoa_base2(ft_atoi(str), "0123456789abcdef");
    len = ft_strlen(tmp->hexa_arg[i + 2]);
    tmp->hexa_arg[i + 2] = padding(tmp->hexa_arg[i + 2], 11);
}

void    arg_to_hexa(t_head *head)
{
    t_code *tmp;
    int i;
    int posi;
    size_t  deci;

    i = 0;
    tmp = head->op_code;
    posi = tmp->position;
    while (tmp)
    {
        while (tmp->arg[i])
        {
            if (tmp->arg[i][0] == 'r')
            {
                if (!(tmp->hexa_arg[i + 2] = (char*)malloc(sizeof(char) * 8)))
                    return ;
                tmp->hexa_arg[i + 2][0] = 'r';
                tmp->hexa_arg[i + 2][1] = tmp->arg[i][1];
                tmp->enc_byte = ft_strcat(tmp->enc_byte, "01");
                tmp->len += 1;
            }
            else if (tmp->arg[i][0] == '%')
            {
                if (!(tmp->hexa_arg[i + 2] = (char*)malloc(sizeof(char) * 12)))
                    return ;
                tmp->hexa_arg[i + 2] = "00 00 00 00\0";
                tmp->enc_byte = ft_strcat(tmp->enc_byte, "10");
                tmp->len += 4;
                get_direct(tmp, i);
            }
            else
            {
                if (!(tmp->hexa_arg[i + 2] = (char*)malloc(sizeof(char) * 8)))
                    return ;
                tmp->hexa_arg[i + 2] = "00 00\0";
                tmp->enc_byte = ft_strcat(tmp->enc_byte, "11");
                tmp->len += 2;
            }

            i++;
        }
        if (i < 4)
        {
            while (i != 4)
            {
                tmp->enc_byte = ft_strcat(tmp->enc_byte, "00");
                i++;
            }
        }
        deci = ft_bi_to_dec(tmp->enc_byte);
        tmp->hexa_arg[1] = ft_itoa_base2(deci, "0123456789abcdef");
        i = 0;
        tmp->position += tmp->len;
        posi = tmp->position;
        tmp = tmp->next;
        if (tmp != NULL)
            tmp->position = posi;
    }
}