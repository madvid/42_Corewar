/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:05:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/10 16:10:03 by armajchr         ###   ########.fr       */
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

int		op_zerojump(t_cw *cw, t_process *p)
{
	int		a;
	int		i;

	if (!p->carry)
		return (i = (cw->options.verbose == true) ? init_verbotab(cw, p, 0) : 0);
	a = (cw->arena[(p->i + 1) % MEM_SIZE]) << 8 \
		| (cw->arena[(p->i + 2) % MEM_SIZE]);
	p->pc = p->i + (a % IDX_MOD);
	return (i = (cw->options.verbose == true) ? init_verbotab(cw, p, 1) : 1);
}

/*
** Function: op_load_index
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_load_index(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	int			a;
	int			b;
	int			c;
	int			i;

	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw->arena, p, p->i + 2, a + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1].direct_size);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1].direct_size);
	c = get_arg_value(cw->arena, p, p->i + 2 + c, REG_CODE);
	p->registers[c - 1] = cw->arena[(p->i + (a + b) % IDX_MOD) % MEM_SIZE];
	return (i = (cw->options.verbose == true) ? init_verbotab(cw, p, 1) : 1);
}

/*
** Function: op_store_index
** Description:
**	This operation writes the value from the registry that was passed as first
**	argument.
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_store_index(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	int			a;
	int			b;
	int			c;
	int			i;

	a = get_arg_value(cw->arena, p, p->i + 2, REG_CODE + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1].direct_size);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1].direct_size);
	c = get_arg_value(cw->arena, p, p->i + 2 + c, ((cw->arena[(p->i + 1) \
		% MEM_SIZE] & 0b00001100) >> 2) + RELATIVE);
	i = -1;
	while (++i < 4)
	{
		cw->arena[(p->i + ((b + c) % IDX_MOD) + i) % MEM_SIZE] \
		= (p->registers[a - 1] & (0xFF000000 >> (8 * i))) >> (24 - (8 * i));
		cw->id_arena[(p->i + ((b + c) % IDX_MOD) + i) % MEM_SIZE] \
		= p->champ->id;
	}
	return (i = (cw->options.verbose == true) ? init_verbotab(cw, p, 1) : 1);
}


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
		return (i = (cw->options.verbose == true) ? init_verbotab(cw, cur_proc, 0) : 0);
	new_proc = (t_process*)(new_link->cnt);
	if (!(new_proc->registers = (int*)ft_memalloc(sizeof(int) * REG_NUMBER)))
	{
		ft_memdel((void **)&new_link);
		return (0);
	}
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
**	1:
**	0: a memory allocation issue occurs during the fork instruction
*/

int		op_fork(t_cw *cw, t_process *cur_proc)
{
	int			addr;

	addr = get_arg_value(cw->arena, cur_proc, cur_proc->i + 1, DIR_CODE);
	if (!fork_creation_process(cw, cur_proc, addr % IDX_MOD)) // check with negative number, during correction with rcourtoi we talk about the issue of '%' with negative nb
		return (-1); // STOP SIGNAL MEMORY ALLOCATION ISSUE
	return ((cw->options.verbose == true) ? init_verbotab(cw, cur_proc, 1) : 1);
}