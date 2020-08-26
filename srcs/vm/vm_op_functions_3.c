/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:05:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/27 00:52:56 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_zerojump
** Description:
**	[put some explanations here !]
** Return:
**	0:
**	-1: otherwise
*/

int		op_zerojump(t_cw *cw, t_process *p)
{
	int		a;

	a = (cw->arena[(p->i + 1) % MEM_SIZE]) << 8 \
		| ((unsigned char)cw->arena[(p->i + 2) % MEM_SIZE]);
	if (!p->carry)
	{
		verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, 0, 0));
		return (-1);
	}
	p->pc = (p->i + (a % IDX_MOD));
	p->pc = (p->pc > 0) ? p->pc % MEM_SIZE : MEM_SIZE + (p->pc % MEM_SIZE);
	verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, 0, 0));
	return (0);
}

/*
** Function: op_load_index
** Description:
**	[put some explanations here !]
** Return:
**	0:
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
		& 0b11000000, op_tab[p->opcode - 1]);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = (a + get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE)) \
		% IDX_MOD + p->i;
	b = (b < 0) ? MEM_SIZE + (b % MEM_SIZE) : b % MEM_SIZE;
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	c = get_arg_value(cw->arena, p, p->i + 2 + c, REG_CODE);
	p->registers[c - 1] = (cw->arena[b] << 24) & 0xFF000000;
	i = 0;
	while (++i < 4)
		p->registers[c - 1] += (((unsigned char)(cw->arena[(b + i) \
			% MEM_SIZE])) << (24 - 8 * i)) & (0xFF000000 >> (8 * i));
	verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, c));
	return (0);
}

/*
** Function: op_store_index
** Description:
**	This operation writes the value from the registry that was passed as first
**	argument.
** Return:
**	0:
*/

int		op_store_index(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	int			a;
	int			b;
	int			c;
	int			i;

	// cw->options->v_p = 1;
	a = get_arg_value(cw->arena, p, p->i + 2, REG_CODE + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	c = (b + get_arg_value(cw->arena, p, p->i + 2 + c, ((cw->arena[(p->i + 1) \
			% MEM_SIZE] & 0b00001100) >> 2) + RELATIVE)) % IDX_MOD + p->i;
	c = (c < 0) ? MEM_SIZE + (c % MEM_SIZE) : c % MEM_SIZE;
	verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, c));
	cw->arena[c % MEM_SIZE] = (a & 0xFF000000) >> 24;
	cw->id_arena[c % MEM_SIZE] = p->champ->id;
	i = 0;
	while (++i < 4)
	{
		cw->arena[(c + i) % MEM_SIZE] = \
			(unsigned char)((a & (0xFF000000 >> (8 * i))) >> (24 - (8 * i)));
		cw->id_arena[(c + i) % MEM_SIZE] = p->champ->id;
	}
	// cw->options->v_p = 0;
	vprint_pcmv(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, c));
	return (0);
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
	static int	id;

	if (!(new_link = ft_lstnew(NULL, sizeof(t_list)))
		|| !(new_proc = (t_process*)ft_memalloc(sizeof(t_process))))
		return (0);
	new_link->cnt = new_proc;
	if (!(new_proc->registers = (int*)ft_memalloc(sizeof(int) * REG_NUMBER)))
	{
		ft_memdel((void **)&(new_link->cnt));
		ft_memdel((void **)&new_link);
		return (0);
	}
	i = -1;
	while (++i < 16)
		new_proc->registers[i] = cur_proc->registers[i];
	new_proc->id = ++id + cw->n_champ;
	new_proc->i = (cur_proc->i + addr) % MEM_SIZE;
	new_proc->i = (new_proc->i < 0) ? MEM_SIZE + new_proc->i : new_proc->i;
	new_proc->carry = cur_proc->carry;
	new_proc->n_lives = cur_proc->n_lives;
	new_proc->last_live = cur_proc->last_live;
	new_proc->wait_cycles = -1;
	new_proc->champ = cur_proc->champ;
	ft_lstadd(&(cw->process), new_link);
	return (1);
}

/*
** Function: op_fork
** Description:
**	[put some explanations here !]
** Return:
**	0: the process is correctly created
**	CD_FORK: a memory allocation issue occurs during the fork instruction
*/

int		op_fork(t_cw *cw, t_process *p)
{
	int			addr;

	addr = get_arg_value(cw->arena, p, p->i + 1, DIR_CODE);
	if (!fork_creation_process(cw, p, addr % IDX_MOD))
		return (vm_error_manager(CD_FORK, NULL, &cw));
	verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, addr, 0, 0));
	return (0);
}
