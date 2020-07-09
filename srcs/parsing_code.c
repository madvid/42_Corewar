/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:16:00 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/09 16:31:52 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/asm.h"

t_code    *is_label(t_code *tmp, char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == ':' && line[i - 1] != '%')
        {
            tmp->label = ft_strncpy(tmp->label, line, i);
            tmp->label[i] = '\0';
            return (tmp);
        }
        i++;
    }
    tmp->label = NULL;
    return (tmp);
}

void    dispatch_info(t_code *tmp, char **s, int argu)
{
    int j;
    int k;

    j = 0;
    k = 0;
    while (j < argu)
    {
        while (s[j][k] == ' ' || s[j][k] == 9)
            k++;
        s[j] = s[j] + k;
        k = 0;
        j++;
    }
    k = 0;
    while (s[0][k] != '\0')
    {
        if (s[0][k] == ' ')
            break;
        tmp->op[k] = s[0][k];
        k++;
    }
    tmp->op[k] = '\0';
    tmp->hexa_arg[0] = tmp->op;
    s[0] += k;
    tmp->arg[0] = s[0];
    if (tmp->arg[0][0])
        tmp->arg[0] += 1;
    (argu <= 3) ? (tmp->arg[1] = s[1]) : (tmp->arg[1] = NULL);
    (argu == 3) ? (tmp->arg[2] = s[2]) : (tmp->arg[2] = NULL);
    tmp->arg[3] = NULL;
}

void    get_op_code_info(t_code *tmp, char *line, int i)
{
    char    **s;
    int     j;
    int     argu;

    line += i;
    argu = 0;
    if (ft_strchr(line, ','))
    {
        s = ft_strsplit(line, ',');
        argu = 3;
    }
    else
    {
        s = ft_strsplit(line, ' ');
        argu = 2;
    }
    j = 0;
    dispatch_info(tmp, s, argu);
    j = 0;
}
