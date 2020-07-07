/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 10:18:52 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/07 16:04:01 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

void    parse(t_head *head, t_code *code, t_label *label, int fd)
{
    char *line;

    while (get_next_line(fd, &line))
    {
        if ((line[0] == '#') || (line[0] == '\0'))
            free(line);
        else if (line[0] == '.')
            ft_is_name(head, line);
        else
            parse_instruction(code, label, line);
    }
}

int     main(int argc, char **argv)
{
    t_head    head;
    t_code    code;
    t_label   label;
    int         fd;

    if (argc != 2)
        return (ft_error_arg());
    fd = open(argv[1], O_RDONLY);
    init_head(&head);
    init_code(&code);
    label = init_label(&label);
    parse(&head, &code, &label, fd);
    ft_printf("info =\n%s\n%s\n", head.name, head.comment);
    ft_printf("code->label = %s\n", code.label);
}