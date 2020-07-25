/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:41:23 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/25 16:57:27 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

/*
** Function: vm_proc_set_lives
** Description:
**	[put some explanations here !]
*/

void	vm_proc_set_lives(t_cw *cw, int set)
{
	t_list		*xplr;
	t_process	*cur_proc;

	xplr = cw->process;
	while (xplr)
	{
		cur_proc = (t_process*)(xplr->cnt);
		cur_proc->n_lives = set;
		xplr = xplr->next;
	}
}

/*
** Function: vm_proc_only_one_standing
** Description:
**	[put some explanations here !]
*/
bool		vm_proc_only_one_standing(t_cw *cw)
{
	int			tmp;
	t_list		*xplr;
	t_process	*cur_proc;

	xplr = cw->process;
	tmp = ((t_process*)(cw->process->cnt))->champ->id;
	while (xplr)
	{
		cur_proc = (t_process*)(xplr->cnt);
		if (tmp != cur_proc->champ->id)
		{
			tmp = -1;
			break;
		}
		xplr = xplr->next;
	}
	return (tmp < 0 ? false : true);
}

/*
** Function: free_one_process
** Description:
**	Function frees the memory allocated to the specified process.
** Remarks:
**	Note that, the function expects an adress of a link pointer (type t_list*)
**	and will free the memory in the process ((t_process*)link->cnt ...) and then
**	the memory of the link pointer.
*/

void		free_one_process(t_list **lst_proc, int id)
{
	int			i;
	t_list		*xplr;
	t_list		*to_del;

	xplr = *lst_proc;
	i = -1;
	if (!xplr)
		return;
	if (((t_process*)(xplr->cnt))->id == id)
	{
		*lst_proc = xplr->next;
		to_del = xplr;
	}
	else
	{
		while (xplr->next && ((t_process*)((xplr)->next->cnt))->id != id)
			xplr = xplr->next;
		to_del = xplr->next;
		xplr->next = xplr->next->next;
	}
	while (++i < REG_NUMBER)
		ft_strdel(&(((t_process*)(to_del->cnt))->registers[i]));
	free(((t_process*)(to_del->cnt))->registers);
	((t_process*)(to_del->cnt))->registers = NULL;
	ft_memdel(&(to_del->cnt));
	ft_memdel((void**)(&(to_del)));
}	

/*
** Function: vm_proc_kill_no_live
** Description:
**	[put some explanations here !]
*/

void		vm_proc_kill_not_living(t_cw *cw)
{
	t_list		*xplr;
	t_list		*tmp;

	if (!cw->process)
		return;
	xplr = cw->process;
	while (xplr)
	{
		if (((t_process*)(xplr->cnt))->n_lives == 0)
		{
			tmp = xplr->next;
			free_one_process(&(cw->process), ((t_process*)(xplr->cnt))->id);
			xplr = tmp;
		}
		else
			xplr = xplr->next;
	}
}

/*
** Function: vm_proc_get_lives
** Description:
**	[put some explanations here !]
** Return:
**	n_lives: total number of lives performed by the processes.
**	-1: Something wrong happen [find what wrong could happen].
*/

int		vm_proc_get_lives(t_cw *cw)
{
	t_list		*xplr;
	t_process	*cur_proc;
	int			n_lives;

	n_lives = 0;
	xplr = cw->process;
	while (xplr)
	{
		cur_proc = (t_process*)(xplr->cnt);
		n_lives += cur_proc->n_lives;
		cw->champ_lives[cur_proc->champ->id - 1] += cur_proc->n_lives;
		xplr = xplr->next;
	}
	return (n_lives);
}

/*
** Function: vm_proc_mv_proc_pos
** Description:
**	Allows to set the process postion and pc to the next value when wait_cycles
**	of the sime processes reach 0 and instruction has been performed
**	(vm_proc_perform_opcode).
**	Precisely, function sets process position, pc, opcode and wait_cycles right
**	after the application of the instruction within process(-es).
*/

void	vm_proc_mv_proc_pos(t_cw *cw)
{
	extern t_op	op_tab[17];
	t_list		*proc;
	t_process	*cur_proc;
	int			op_pos;

	proc = cw->process;
	while (proc)
	{
		cur_proc = ((t_process*)(proc->cnt));
		if (cur_proc->wait_cycles == 0)
		{
			printf("a proc has it wait_cycles to 0\n");
			printf("~~~~~ BEFORE MOVE ~~~~~\n");
			tool_print_processor(cur_proc, cur_proc->id);
			cur_proc->position = cur_proc->pc;
			op_pos = cur_proc->position - (void*)(cw->arena);
			cur_proc->pc = addr_next_opcode(cw->arena, op_pos);
			printf("");
			cur_proc->opcode = cw->arena[op_pos];
			cur_proc->wait_cycles = op_tab[(int)(cur_proc->opcode) - 1].cycle;
			printf("~~~~~ AFTER MOVE ~~~~~\n");
			tool_print_processor(cur_proc, cur_proc->id);
		}
		proc = proc->next;
	}
}

/*
** Function: vm_proc_perform_opcode
** Description:
**	[put some explanations !]
*/

void	vm_proc_perform_opcode(t_cw *cw)
{
	t_list		*xplr;
	t_process	*cur_proc;

	xplr = cw->process;
	while (xplr)
	{
		cur_proc = (t_process*)(xplr->cnt);
		if (cur_proc->wait_cycles == 0)
			perform_opcode(cw, cur_proc);
		xplr = xplr->next;
	}
}

/*
** Function: vm_proc_cycle
** Description:
**	[put some explanations]
** Return:
**	1: All processes have there wait_cycles decreased by 1.
**	0: At least one process has wait_cycles at 0 before the decrementation.
*/

void	vm_proc_cycle(t_cw *cw)
{
	t_list		*xplr;
	t_process	*cur_proc;

	xplr = cw->process;
	while (xplr)
	{
		cur_proc = (t_process*)(xplr->cnt);
		cur_proc->wait_cycles -= 1;
		xplr = xplr->next;
	}
}