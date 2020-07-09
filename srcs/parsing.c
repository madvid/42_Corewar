/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 10:18:52 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/09 14:14:32 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

void    parse_instruction(t_head *head, char *line)
{
    int i;
    t_code  *tmp;

    tmp = head->op_code;
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

void    parse(t_head *head, int fd)
{
    char *line;

    while (get_next_line(fd, &line))
    {
        if ((line[0] == '#') || (line[0] == '\0'))
            free(line);
        else if (line[0] == '.')
            ft_is_name(head, line);
        else
            parse_instruction(head, line);
    }
}

int     main(int argc, char **argv)
{
    t_head    head;

    int         fd;

    if (argc != 2)
        return (ft_error_arg());
    fd = open(argv[1], O_RDONLY);
    init_head(&head);
    parse(&head, fd);
    arg_to_hexa(&head);
    instruction_to_hexa(&head);
    print_op_code(&head);
}