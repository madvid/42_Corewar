/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:06:21 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/30 17:47:24 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_long_load
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_long_load(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int			index;
	int			a;
	int			b;

	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	a = (cw->arena[(index + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw, cur_proc, index + 2, a);
	if (((cw->arena[(index + 1) % MEM_SIZE] & 0b11000000) >> 6) == IND_CODE)
		a = cw->arena[(index + a /*% IDX_MOD*/) % MEM_SIZE];
		//on ne coupe pas la valeur IND_CODE avec IDX_MOD contrairement au ld simple
	b = instruction_width(cw->arena[(index + 1) % MEM_SIZE] \
		& 0b11000000, op_elem.direct_size);
	b = get_arg_value(cw, cur_proc, index + 2 + b, REG_CODE);
	cur_proc->carry = (a == 0) ? 1 : 0;
	cur_proc->registers[b - 1] = a;
	return (1);
}

/*
** Function: op_long_load_index
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_long_load_index(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int			index;
	int			a;
	int			b;
	int			c;

	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	a = (cw->arena[(index + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw, cur_proc, index + 2, a + RELATIVE);
	if (((cw->arena[(index + 1) % MEM_SIZE] & 0b11000000) >> 6) == REG_CODE)
	{
		if (a > REG_NUMBER || a < 1)
			return (0);
		a = cur_proc->registers[a - 1];
	}
	c = instruction_width(cw->arena[(index + 1) % MEM_SIZE] \
		& 0b11000000, op_elem.direct_size);
	b = (cw->arena[(index + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw, cur_proc, index + 2 + c, b + RELATIVE);
	if (((cw->arena[(index + 1) % MEM_SIZE] & 0b00110000) >> 4) == REG_CODE)
	{
		if (b > REG_NUMBER || b < 1)
			return (0);
		b = cur_proc->registers[b - 1];
	}
	c = instruction_width(cw->arena[(index + 1) % MEM_SIZE] \
		& 0b11110000, op_elem.direct_size);
	c = get_arg_value(cw, cur_proc, index + 2 + c, REG_CODE);
	if (c > REG_NUMBER || c < 1)
		return (0);
	cur_proc->carry = (a == 0) ? 1 : 0;
	cur_proc->registers[c - 1] = cw->arena[(index + (a + b) % IDX_MOD) % MEM_SIZE];
	return (1);
}

/*
** Function: op_long_fork
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_long_fork(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int			index;
	int			addr;

	printf("Long fork instruction en cours\n");
	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	addr = (cw->arena[(index + 1) % MEM_SIZE] & 255) << 24
		| (cw->arena[(index + 2) % MEM_SIZE] & 255) << 16
		| (cw->arena[(index + 3) % MEM_SIZE] & 255) << 8
		| (cw->arena[(index + 4) % MEM_SIZE] & 255);
	if (!fork_creation_process(cw, cur_proc, addr)) // check with negative number, during correction with rcourtoi we talk about the issue of '%' with negative nb
		return (-1); // STOP SIGNAL MEMORY ALLOCATION ISSUE
	return (1);
}

/*
** Function: op_aff
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_aff(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int			index;
	int			arg;
	u_int8_t	reg;

	printf("Aff instruction en cours\n");
	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	reg = (u_int8_t)cw->arena[(index + 2) % MEM_SIZE];
	if (reg < 1 || reg > REG_NUMBER)
		return (0);
	arg = cur_proc->registers[reg - 1];
	if (cw->options.aff == true)
		printf("Aff: %s\n", ft_itoa(arg)); // switch avec ft_printf
	return (0);
}
