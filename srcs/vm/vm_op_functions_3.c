/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:05:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/30 18:07:30 by mdavid           ###   ########.fr       */
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

int		op_zerojump(t_cw *cw, t_process *cur_proc)
{
	int		a;

	if (!cur_proc->carry)
		return (0);
	a = (cw->arena[(cur_proc->i + 1) % MEM_SIZE]) << 8 \
		| (cw->arena[(cur_proc->i + 2) % MEM_SIZE]);
	cur_proc->pc = cur_proc->i + (a % IDX_MOD);
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

int		op_load_index(t_cw *cw, t_process *cur_proc)
{
	extern t_op	op_tab[17];
	int			a;
	int			b;
	int			c;

	a = (cw->arena[(cur_proc->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw, cur_proc, cur_proc->i + 2, a + RELATIVE);
	if (((cw->arena[(cur_proc->i + 1) % MEM_SIZE] & 0b11000000) >> 6) == REG_CODE)
	{
		if (a > REG_NUMBER || a < 1)
			return (0);
		a = cur_proc->registers[a - 1];
	}
	c = instruction_width(cw->arena[(cur_proc->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[cur_proc->opcode - 1].direct_size);
	b = (cw->arena[(cur_proc->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw, cur_proc, cur_proc->i + 2 + c, b + RELATIVE);
	if (((cw->arena[(cur_proc->i + 1) % MEM_SIZE] & 0b00110000) >> 4) == REG_CODE)
	{
		if (b > REG_NUMBER || b < 1)
			return (0);
		b = cur_proc->registers[b - 1];
	}
	c = instruction_width(cw->arena[(cur_proc->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[cur_proc->opcode - 1].direct_size);
	c = get_arg_value(cw, cur_proc, cur_proc->i + 2 + c, REG_CODE);
	if (c > REG_NUMBER || c < 1)
		return (0);
	cur_proc->carry = (a == 0) ? 1 : 0;
	cur_proc->registers[c - 1] = cw->arena[(cur_proc->i + (a + b) % IDX_MOD) % MEM_SIZE];
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

/*int		op_store_index(t_cw *cw, t_process *cur_proc)
{
	...;
}*/


/*
** Function:
** Description:
**	The function will creates a new process and copy the value of the inner
**	variables of the parent process into the new one, except for the pc
** Remarks:
**	As we copy everything, it is not bothering to copy i, wait_cycle
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
	i = cur_proc->i;
	new_proc->pc = i + addr;
	new_proc->id = ((t_process*)(cw->process->cnt))->id + 1;
	new_proc->n_lives = 0;
	new_proc->wait_cycles = 0;
	new_proc->i = cur_proc->i;
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

int		op_fork(t_cw *cw, t_process *cur_proc)
{
	int			addr;

	printf("Fork instruction en cours\n");
	addr = (cw->arena[(cur_proc->i + 1) % MEM_SIZE] & 255) << 24
		| (cw->arena[(cur_proc->i + 2) % MEM_SIZE] & 255) << 16
		| (cw->arena[(cur_proc->i + 3) % MEM_SIZE] & 255) << 8
		| (cw->arena[(cur_proc->i + 4) % MEM_SIZE] & 255);
	if (!fork_creation_process(cw, cur_proc, addr % IDX_MOD)) // check with negative number, during correction with rcourtoi we talk about the issue of '%' with negative nb
		return (-1); // STOP SIGNAL MEMORY ALLOCATION ISSUE
	return (1);
}