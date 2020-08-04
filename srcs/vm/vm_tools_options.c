/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:22:58 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/04 12:27:10 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	int		j;
	
	i = 0;
	while (i < MEM_SIZE && arena)
	{
		j = 0;
		ft_printf("0x%.4x :", i);
		while (j < 64)
		{
			ft_printf(" %2.2x", (u_int8_t)arena[i + j]);
			j++;
		}
		ft_putchar('\n');
		i = i + j;
	}
	return (DUMP_SIG);
}
