/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:26:30 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/10 11:25:38 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

int     main(int ac, char **av)
{
    t_head      head;

    if (ac != 2)
        leave(&head, ": Number of argv is not correct !\n");
    init_head(&head, av[1]);
    parse(&head, h.i);
    arg_to_hexa(&head);
    instruction_to_hexa(&head);
    print_op_code(&head);
}