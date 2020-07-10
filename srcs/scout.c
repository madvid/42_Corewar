/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 12:58:36 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/10 13:30:40 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

int     is_white(char c)
{
    if (c == ' ' || c == 9 || c == '\n' || c == '\r' || c == '\v' || c == '\f')
        return (1);
    return (0);
}

int     is_head(char *s)
{
    char    c;

    c = *s + NAME_CMD_STRING;
    if (ft_strnequ(s, NAME_CMD_STRING, 5) && (is_white(c) || c == '"'))
        return (1);
    return (0);
}

int     is_com(t_head *h, char c)
{
    if (c == COMMENT_CHAR)
    {
        while (h->buff[h->i] !='\n' || h->buff[h->i] !='\0')
            h->i++;
        return (1);
    }
    return (0);
}

int     is_instruction(char *s, int i)
{
    while (is_white(s[i]))
    {
        if (s[i] == '\n')
            return (0);
        i++;
    }
}

int     is_label(char *s, int i)
{
    int     j;

    j = 0;
    while (ft_strchrf(LABEL_CHARS, s[j + i], 0) >= 0)
        j++;
    if (s[j + i] == ":" && j > 0)
        return (1);
    return (0);
}