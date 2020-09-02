/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:05:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/02 16:28:44 by armajchr         ###   ########.fr       */
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

int			op_zerojump(t_cw *cw, t_process *p)
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

int			op_load_index(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	t_arg		v_arg;
	int			ag[3];

	op_arg_init(&v_arg, DIR_CODE, 3);
	ag[0] = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	ag[0] = get_arg_value(cw, p, p->i + 2, ag[0] + RELATIVE);
	v_arg.arg[0] = ag[0];
	ag[2] = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	ag[1] = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	v_arg.arg[1] = get_arg_value(cw, p, p->i + 2 + ag[2], \
		ag[1] + RELATIVE);
	ag[1] = (ag[0] + v_arg.arg[1]) % IDX_MOD + p->i;
	ag[1] = (ag[1] < 0) ? MEM_SIZE + (ag[1] % MEM_SIZE) : ag[1] % MEM_SIZE;
	ag[2] = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	ag[2] = get_arg_value(cw, p, p->i + 2 + ag[2], REG_CODE);
	v_arg.arg[2] = ag[2];
	v_arg.type[2] = REG_CODE;
	p->registers[ag[2] - 1] = (cw->arena[ag[1]] << 24) & 0xFF000000;
	write_in_reg(cw, p, ag);
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

int			op_store_index(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	t_arg		v_arg;
	int			arg[3];
	int			encod;

	op_arg_init(&v_arg, DIR_CODE, 7);
	v_arg.type[0] = REG_CODE;
	v_arg.arg[0] = get_arg_value(cw, p, p->i + 2, REG_CODE);
	arg[0] = p->registers[v_arg.arg[0] - 1];
	arg[2] = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	encod = cw->arena[(p->i + 1) % MEM_SIZE];
	arg[1] = get_arg_value(cw, p, p->i + 2 + arg[2]\
		, ((encod & 0b00110000) >> 4) + RELATIVE);
	v_arg.arg[1] = arg[1];
	arg[2] = instruction_width(encod & 0b11110000, op_tab[p->opcode - 1]);
	v_arg.arg[2] = get_arg_value(cw, p, p->i + 2 + arg[2]\
		, ((encod & 0b00001100) >> 2) + RELATIVE);
	arg[2] = (arg[1] + v_arg.arg[2]) % IDX_MOD + p->i;
	arg[2] = (arg[2] < 0) ? MEM_SIZE + (arg[2] % MEM_SIZE) : arg[2] % MEM_SIZE;
	write_in_arena(cw, p, arg);
	verbotab(cw, p, v_arg);
	return (0);
}

/*
** Function: init_newproc_fork
** Description:
**	Initiates the differents arguments of the new processus created
**	by the fork.
*/

static void	init_newproc_fork(t_process *new_proc, t_process *cur_proc)
{
	int			i;

	i = -1;
	while (++i < 16)
		new_proc->registers[i] = cur_proc->registers[i];
	new_proc->carry = cur_proc->carry;
	new_proc->n_lives = cur_proc->n_lives;
	new_proc->last_live = cur_proc->last_live;
	new_proc->wait_cycles = -1;
	new_proc->champ = cur_proc->champ;
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

int			fork_creation_process(t_cw *cw, t_process *cur_proc, int addr)
{
	t_list		*new_link;
	t_process	*new_proc;
	static int	id;

	if (!(new_link = ft_lstnew(NULL))
		|| !(new_proc = (t_process*)ft_memalloc(sizeof(t_process))))
		return (0);
	new_link->cnt = new_proc;
	if (!(new_proc->registers = (int*)ft_memalloc(sizeof(int) * REG_NUMBER)))
	{
		ft_memdel((void **)&(new_link->cnt));
		ft_memdel((void **)&new_link);
		return (0);
	}
	new_proc->id = ++id + cw->n_champ;
	new_proc->i = (cur_proc->i + addr) % MEM_SIZE;
	new_proc->i = (new_proc->i < 0) ? MEM_SIZE + new_proc->i : new_proc->i;
	init_newproc_fork(new_proc, cur_proc);
	ft_lstadd(&(cw->process), new_link);
	return (1);
}
