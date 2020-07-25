/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:04:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/25 15:59:38 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_alive
** Description:
**	[put some explanations here !]
** Remarks:
**	The instruction alive allow to increment the live counter of the process
**	and the number of lives of the different champions.
**	There is no encoding byte, thus the argument of type direct (even if it is
**	not a direct argument) is parse.
**	If the argument correspond to a champion id, the number of live of the
**	corresponding champion (cw->champ_lives[x]) is increased, and the nb of
**	lives made by the process also as long as the champ id is a correct one.
** Return:
**	1:	the instruction is valid (= encoding byte coherent) or no encoding byte
**		needed by the instruction thus it is performed in any case.
**	0:	if the encoding byte is not coherent with what the instruction takes
**		as argument(s).
*/

int		op_alive(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		arg;

	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	arg = (cw->arena[(index + 1) % MEM_SIZE] & 255) << 24
		| (cw->arena[(index + 2) % MEM_SIZE] & 255) << 16
		| (cw->arena[(index + 3) % MEM_SIZE] & 255) << 8
		| (cw->arena[(index + 4) % MEM_SIZE] & 255);
	cur_proc->n_lives++; // even if the arg contain a non valid champ id.
	if (arg > 0 && arg < cw->n_champ) // not sure for this, is alive instruction always valid as long as the argument is a positive int ? or in every case ?
	{
		cw->champ_lives[arg - 1]++;
		return (1);
	}
	return (1);
}

/*
** Function: op_load
** Description:
**	[put some explanations here !]
** Return:
**	1:
**	0:
*/

/*int		op_load(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		arg;

	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	
	return (1);
}*/

/*
** Function: op_store
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

// int		op_store(t_cw *cw, t_process *cur_proc, t_op op_elem)
// {
// 	...;
// }

/*
** Function: op_adition
** Description:
**	[put some explanations here !]
** Return:
**	[]:
**	[]:
*/

// int		op_addition(t_cw *cw, t_process *cur_proc, t_op op_elem)
// {
// 	...;
// }
