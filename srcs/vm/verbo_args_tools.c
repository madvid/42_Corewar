/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbo_args_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 13:07:22 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/26 13:09:26 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function:
**
**
*/

t_arg	op_arg(int encod, t_process *p, int *arg)
{
	extern t_op	op_tab[17];
	t_arg	ag;

	if (encod == 0)
	{
		i = -1;
		while(++i < 3)
			ag.type[i] = (op_tab[p->opcode -1].n_arg >= i + 1) ? \
				op_tab[p->opcode -1].type[i] : 0;
	}
	else
	{
		i = -1;
		while (++i < 3)
		{
			ag.type[i] = (op_tab[p->opcode -1].n_arg >= i + 1) ? \
				(encod & 192) >> (8 - 2 * (i + 1)) : 0;
			if (op_tab[p->opcode -1].n_arg >= i + 1)
				ag.type[i] = (ag.type[i] == 3) ? \
				4 & op_tab[p->opcode -1].type[0] \
				: ag.type[i] & op_tab[p->opcode -1].type[i];
		}
	}
}