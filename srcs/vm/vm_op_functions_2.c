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
	a = cw->arena[(index + 2) % MEM_SIZE];
	b = cw->arena[(index + 3) % MEM_SIZE];
	c = cw->arena[(index + 4) % MEM_SIZE];
	if (a < 1 || a > REG_NUMBER || b < 1 || b > REG_NUMBER \
		|| c < 1 || c > REG_NUMBER)
		return (0);
	cur_proc->registers[c - 1] = cur_proc->registers[a - 1] - cur_proc->registers[b - 1];
	cur_proc->carry = (cur_proc->registers[c - 1] == 0) ? 1 : 0;
	return (1);
}

/*
** Function: op_and
** Description:
**	Normalement ça marche
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

	index = cur_proc->position - (void *)(cw->arena);
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
	b = get_arg_value(cw, index + 2 + c, a + RELATIVE);
	if (((cw->arena[(index + 1) % MEM_SIZE] & 0b00110000) >> 4) == REG_CODE)
		if (b < 1 | b > REG_NUMBER)
			return (0);
	c = instruction_width(cw->arena[(index + 1) % MEM_SIZE] \
		& 0b11110000, op_elem->direct_size);
	c = get_arg_value(cw, index + 2 + c, REG_CODE);
	if (c < 1 | c > REG_NUMBER)
		return (0);
	cur_proc->registers[c] = a & b;
	cur_proc->carry = (cur_proc->registers[c] = a & b) ? 1 : 0;
	return (1);
}

/*
** Function: op_or
** Description:
**	Comme op_and
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_or(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		a;
	int		b;
	int		c;

	index = cur_proc->position - (void *)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	a = (cw->arena[(index + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw, index + 2, a + RELATIVE);
	c = instruction_width(cw->arena[(index + 1) % MEM_SIZE] \
		& 0b11000000, op_elem->direct_size);
	b = (cw->arena[(index + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw, index + 2 + c, a + RELATIVE);
	c = instruction_width(cw->arena[(index + 1) % MEM_SIZE] \
		& 0b11110000, op_elem->direct_size);
	c = get_arg_value(cw, index + 2 + c, REG_CODE);
	cur_proc->registers[c] = a & b;
	cur_proc->carry = (cur_proc->registers[c] = a | b) ? 1 : 0;
	return (1);
}

/*
** Function: op_xor
** Description:
**	Idem
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_xor(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		a;
	int		b;
	int		c;

	index = cur_proc->position - (void *)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	a = (cw->arena[(index + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw, index + 2, a + RELATIVE);
	c = instruction_width(cw->arena[(index + 1) % MEM_SIZE] \
		& 0b11000000, op_elem->direct_size);
	b = (cw->arena[(index + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw, index + 2 + c, a + RELATIVE);
	c = instruction_width(cw->arena[(index + 1) % MEM_SIZE] \
		& 0b11110000, op_elem->direct_size);
	c = get_arg_value(cw, index + 2 + c, REG_CODE);
	cur_proc->registers[c] = a & b;
	cur_proc->carry = (cur_proc->registers[c] = a ^ b) ? 1 : 0;
	return (1);
}

