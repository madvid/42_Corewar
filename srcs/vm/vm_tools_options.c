/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:22:58 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/03 18:54:02 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

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
	while (i < MEM_SIZE)
	{
		ft_printf("0x%X : %s\n", i, "toto");
		i = i + 65;
	}
	return (DUMP_SIG);
}