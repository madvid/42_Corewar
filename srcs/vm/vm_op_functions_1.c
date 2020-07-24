/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:04:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/24 17:02:09 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_alive
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_alive(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		arg;

	index = cur_proc->position - (void*)(cw->arena);
	// verification du byte d'encodage-> NON, car aliv n'a pas de byte d'encodage:
	arg = (cw->arena[(index + 1) % MEM_SIZE] & 255) << 24
		| (cw->arena[(index + 2) % MEM_SIZE] & 255) << 16
		| (cw->arena[(index + 3) % MEM_SIZE] & 255) << 8
		| (cw->arena[(index + 4) % MEM_SIZE] & 255);
	// printf("[op_alive] valeur de arg = %d\n", arg);
	if (arg == ((int)cur_proc->registers[0] & 2)
	// choper l'argument; (verifier avec le byte d'encodage que le champ d'argument est valide)
	// comparer l'argument avec le contenue de r1: cur_proc->registers[0]
	// si identique
	// 	augmenter de 1 cur_proc->nb_lives
	// ...;
}

/*
** Function: op_load
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

// int		op_load(t_cw *cw, t_process *cur_proc, t_op op_elem)
// {
// 	...;
// }

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
