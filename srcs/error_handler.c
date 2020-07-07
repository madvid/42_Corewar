/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:35:48 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/07 15:31:38 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

int     ft_error_arg(void)
{
    ft_printf("Too many arguments for asm exe\nUsage : ./asm <file.s>");
    return (-1);
}