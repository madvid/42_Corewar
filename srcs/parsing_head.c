/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_head.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:16:29 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/07 15:31:34 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

void    ft_get_name(t_head *head, char *line)
{
    int i;
    int j;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == ' ' || line[i] == '"')
            break ;
        i++;
    }
    line[i] == ' ' ? i = i + 2: i++;
    j = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '"')
            break ;
        head->name[j] = line[i];
        i++;
        j++;
    }
}

void    ft_get_comment(t_head *head, char *line)
{
    int i;
    int j;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == ' ' || line[i] == '"')
            break ;
        i++;
    }
    line[i] == ' ' ? i = i + 2: i++;
    j = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '"')
            break ;
        head->comment[j] = line[i];
        i++;
        j++;
    }
}

/**Recuperation du .name et .comment dans la struct s_head**/
void    ft_is_name(t_head *head, char *line)
{
    if (ft_strncmp(line, NAME_CMD_STRING, 5) == 0)
        ft_get_name(head, line);
    else if (ft_strncmp(COMMENT_CMD_STRING, line, 8) == 0)
        ft_get_comment(head, line);
    free(line);
}
