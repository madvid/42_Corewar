/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:05:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/24 14:17:19 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_soustraction
** Description:
**	- Writes in cur_proc->registers[ARG_3] the value
**    cur_proc->registers[ARG_1] - cur_proc->registers[ARG_2]
**  - cur->carry = 1 (if value == 0)
**                 0 (else)
** Return:
**	[value_1]: 1 if encoding byte and arguments are valid
**	[value_2]: 0 else
*/

int		op_soustraction(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		a;
	int		b;
	int		c;

	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	a = (cw->arena[(index + 2) % MEM_SIZE] & 255);
	b = (cw->arena[(index + 3) % MEM_SIZE] & 255);
	c = (cw->arena[(index + 4) % MEM_SIZE] & 255)
	if (a < 0 || a > 99 || b < 0 || b > 99 || c < 0 || c > 99)	//valeurs limites à revoir
		return (0);
	cur_proc->registers[c] = cur_proc->registers[a] - cur_proc->registers[b];
	cur_proc->carry = (cur_proc->registers[c] == 0) ? 1 : 0;
	return (1);
}

/*
** Function: op_and
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_and(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		a;
	int		b;
	int		c;

	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	if (((encoding & 0b11000000) >> 6) == 1 || ((encoding & 0b00110000) >> 4) == 1)
		(((encoding & 0b11000000) >> 6) == 1) \
		? a = (cw->arena[(index + 2) % MEM_SIZE] & 255) \
		: b = (cw->arena[(index + len(type_a)) % MEM_SIZE] & 255)

}

/*
** Function: op_or
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_or(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	...;
}

/*
** Function: op_xor
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_xor(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	...;
}

