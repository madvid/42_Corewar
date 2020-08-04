/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:22:58 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/04 09:31:52 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
//#include "ft_printf.h"

/*
** Function: dump_memory
** Description:
**	print on standard output the arena memory state at the dump_cycle cycles
**	after the beginning of the "battle".
** Return:
**	DUMP_SIG: signal of the dump operation.
*/

int		dump_memory(char *arena)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE && arena)
	{
		printf("0x%X : %s\n", i, "toto");
		i = i + 65;
	}
	return (DUMP_SIG);
}