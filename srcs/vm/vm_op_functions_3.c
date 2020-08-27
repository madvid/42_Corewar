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
	t_arg		v_arg;
	int			a;

	op_arg_init(&v_arg, DIR_CODE, 1);
	a = (cw->arena[(p->i + 1) % MEM_SIZE]) << 8 \
		| ((unsigned char)cw->arena[(p->i + 2) % MEM_SIZE]);
	v_arg.arg[0] = a;
	if (!p->carry)
	{
		verbotab(cw, p, v_arg);
		return (-1);
	}
	p->pc = (p->i + (a % IDX_MOD));
	p->pc = (p->pc > 0) ? p->pc % MEM_SIZE : MEM_SIZE + (p->pc % MEM_SIZE);
	verbotab(cw, p, v_arg);
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
	t_arg		v_arg;
	int			arg[3];
	int			i;

	op_arg_init(&v_arg, DIR_CODE, 3);
	arg[0] = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	arg[0] = get_arg_value(cw->arena, p, p->i + 2, arg[0] + RELATIVE);
	v_arg.arg[0] = arg[0];
	arg[2] = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	arg[1] = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	v_arg.arg[1] = get_arg_value(cw->arena, p, p->i + 2 + arg[2], arg[1] + RELATIVE);
	arg[1] = (arg[0] + v_arg.arg[1]) % IDX_MOD + p->i;
	arg[1] = (arg[1] < 0) ? MEM_SIZE + (arg[1] % MEM_SIZE) : arg[1] % MEM_SIZE;
	arg[2] = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	arg[2] = get_arg_value(cw->arena, p, p->i + 2 + arg[2], REG_CODE);
	v_arg.arg[2] = arg[2];
	v_arg.type[2] = REG_CODE;
	p->registers[arg[2] - 1] = (cw->arena[arg[1]] << 24) & 0xFF000000;
	i = 0;
	while (++i < 4)
		p->registers[arg[2] - 1] += (((unsigned char)(cw->arena[(arg[1] + i) \
			% MEM_SIZE])) << (24 - 8 * i)) & (0xFF000000 >> (8 * i));
	verbotab(cw, p, v_arg);
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
	t_arg		v_arg;
	int			arg[3];

	op_arg_init(&v_arg, DIR_CODE, 7);
	v_arg.type[0] = REG_CODE;
	v_arg.arg[0] = get_arg_value(cw->arena, p, p->i + 2, REG_CODE);
	arg[0] = p->registers[v_arg.arg[0] - 1];
	arg[2] = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	arg[1] = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	arg[1] = get_arg_value(cw->arena, p, p->i + 2 + arg[2], arg[1] + RELATIVE);
	arg[2] = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	arg[2] = (arg[1] + get_arg_value(cw->arena, p, p->i + 2 + arg[2], ((cw->arena[(p->i + 1) \
			% MEM_SIZE] & 0b00001100) >> 2) + RELATIVE)) % IDX_MOD + p->i;
	arg[2] = (arg[2] < 0) ? MEM_SIZE + (arg[2] % MEM_SIZE) : arg[2] % MEM_SIZE;
	write_in_arena(cw, p, arg);
	verbotab(cw, p, v_arg);
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
	t_arg		v_arg;
	int			addr;

	op_arg_init(&v_arg, DIR_CODE, 1);
	addr = get_arg_value(cw->arena, p, p->i + 1, DIR_CODE);
	v_arg.arg[0] = addr;
	if (!fork_creation_process(cw, p, addr % IDX_MOD))
		return (CD_FORK);
	verbotab(cw, p, v_arg);
	return (0);
}
