/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:05:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/30 17:29:47 by mdavid           ###   ########.fr       */
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
/*
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
*/
/*
** Function: op_store_index
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/
/*
int		op_store_index(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	...;
}
*/

/*
** Function:
** Description:
**	The function will creates a new process and copy the value of the inner
**	variables of the parent process into the new one, except for the pc
** Remarks:
**	As we copy everything, it is not bothering to copy position, wait_cycle
**	being zero, the new process will move to the given addr at the next cycle
** Return:
**	1: the creation of the new process succedeed
**	0: otherwise.
*/

int		fork_creation_process(t_cw *cw, t_process *cur_proc, int addr)
{
	t_list		*new_link;
	t_process	*new_proc;
	int			i;

	if (!(new_link = ft_lstnew((void*)(cur_proc), sizeof(t_process))))
		return (0);
	new_proc = (t_process*)(new_link->cnt);
	if (!(new_proc->registers = (int*)ft_memalloc(sizeof(int) * REG_NUMBER)))
		return (0);
	i = -1;
	while (++i < 16)
		new_proc->registers[i] = cur_proc->registers[i];
	if (!(new_proc->pc = ft_memalloc(REG_SIZE)))
		return (0);
	i = cur_proc->position - (void*)(cw->arena);
	new_proc->pc = (void*)(&(cw->arena[i + addr]));
	new_proc->id = ((t_process*)(cw->process->cnt))->id + 1;
	new_proc->n_lives = 0;
	new_proc->wait_cycles = 0;
	new_proc->position = cur_proc->position;
	new_proc->champ = cur_proc->champ;
	ft_lstadd(&(cw->process), new_link);
	return (1);
}

/*
** Function: op_fork
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	-1: a memory allocation issue occurs during the fork instruction
*/

int		op_fork(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int			index;
	int			addr;

	printf("Fork instruction en cours\n");
	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	addr = (cw->arena[(index + 1) % MEM_SIZE] & 255) << 24
		| (cw->arena[(index + 2) % MEM_SIZE] & 255) << 16
		| (cw->arena[(index + 3) % MEM_SIZE] & 255) << 8
		| (cw->arena[(index + 4) % MEM_SIZE] & 255);
	if (!fork_creation_process(cw, cur_proc, addr % IDX_MOD)) // check with negative number, during correction with rcourtoi we talk about the issue of '%' with negative nb
		return (-1); // STOP SIGNAL MEMORY ALLOCATION ISSUE
	return (1);
}