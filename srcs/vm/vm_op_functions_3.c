/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:05:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/24 14:18:30 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_zerojump
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_zerojump(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		a;

	if (!cur_proc->carry)
		return (0);
	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	a = (cw->arena[(index + 1) % MEM_SIZE]) << 8 \
		| (cw->arena[(index + 2) % MEM_SIZE]);
	cur_proc->pc = cur_proc->position + (a % IDX_MOD);
	return (1);
}

/*
** Function: op_load_index
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_load_index(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		a;
	int		b;

	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	a = (cw->arena[(index + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw, index + 2, a + RELATIVE);
	if (((cw->arena[(index + 1) % MEM_SIZE] & 0b11000000) >> 6) == REG_CODE)
		if (a < 1 | a > REG_NUMBER)
			return (0);
	c = instruction_width(cw->arena[(index + 1) % MEM_SIZE] \
		& 0b11000000, op_elem->direct_size);
	b = (cw->arena[(index + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw, index + 2 + c, b + RELATIVE);
	if (((cw->arena[(index + 1) % MEM_SIZE] & 0b00110000) >> 4) == REG_CODE)
		if (b < 1 | b > REG_NUMBER)
			return (0);
	c = instruction_width(cw->arena[(index + 1) % MEM_SIZE] \
		& 0b11110000, op_elem->direct_size);
	c = get_arg_value(cw, index + 2 + c, REG_CODE);
	if (c < 1 | c > REG_NUMBER)
		return (0);
	cur_proc->registers[c - 1] = cw->arena[index + (a + b) % IDX_MOD];
	return (1);
}

/*
** Function: op_store_index
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_store_index(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	...;
}

/*
** Function: op_fork
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_fork(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	...;
}
