/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:41:23 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/24 12:12:14 by mdavid           ###   ########.fr       */
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
	free(((t_process*)(to_del->cnt))->registers);
	((t_process*)(to_del->cnt))->registers = NULL;
	ft_memdel(&(to_del->cnt));
	ft_memdel((void**)(&(to_del)));
}	

/*
** Function: vm_proc_kill_no_live
** Description:
**	[put some explanations here !]
** Return:
**	1: if at least one process remaind in the list cw->process after killing
**		concerned processes.
**	0: if no process remainds or if the number of processes exceed INT_MAX
*/

int		vm_proc_kill_not_living(t_cw *cw)
{
	t_list		*xplr;
	t_list		*next;
	t_list		*before;

	xplr = cw->process;
	before = cw->process;
	while (xplr)
	{
		if (((t_process*)(xplr->cnt))->n_lives == 0)
		{
			next = xplr->next;
			if (cw->options->v_lvl & 0b1000)
				vprint_deaths(cw, (t_process*)(xplr->cnt), 1);
			ft_lst_fdel_proc(xplr, xplr->cnt_s);
			before->next = next;
			xplr = next;
		}
		else
		{
			before = xplr;
			xplr = xplr->next;
		}
	}
	return ((ft_lst_len(cw->process) == 0) ? 0 : 1);
}

/*
** Function: vm_proc_get_lives
** Description:
**	[put some explanations here !]
** Return:
**	n_lives: total number of lives performed by the processes.
**	0: if no alive has been made.
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
	cw->tot_lives += n_lives;
	cw->ctd_lives = n_lives;
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

void	vm_proc_mv_proc_pos(t_cw *cw, t_process *proc)
{
	extern t_op	op_tab[17];

	if (proc->wait_cycles == -1)
	{
		proc->opcode = cw->arena[proc->i];
		if (proc->opcode >= 1 && proc->opcode <= 16)
			proc->wait_cycles = op_tab[proc->opcode - 1].cycle;
		else
			proc->wait_cycles = 1;
		proc->pc = addr_next_opcode(cw->arena, proc);
	}
	else if (proc->wait_cycles == 0)
	{
		proc->i = proc->pc;
		proc->wait_cycles = -1;
		// proc->pc = addr_next_opcode(cw->arena, proc);
		// proc->opcode = cw->arena[proc->i];
		// if (proc->opcode >= 1 && proc->opcode <= 16)
		// 	proc->wait_cycles = op_tab[proc->opcode - 1].cycle;
		// else
		// 	proc->wait_cycles = 1;
	}
}

/*
** Function: vm_proc_perform_opcode
** Description:
**	[put some explanations !]
** Return:
**	code_error: value of the corresponding error
**	0: No error/issue occured
*/

int		vm_proc_perform_opcode(t_cw *cw)
{
	int			code_error;
	t_list		*xplr;
	t_process	*cur_proc;
	int			opfork;

	code_error = 0;
	xplr = cw->process;
	while (xplr)
	{
		cur_proc = (t_process*)(xplr->cnt);
		if (cur_proc->wait_cycles == 0)
		{
			// tool_print_processor(cur_proc, cur_proc->id);
			if ((code_error = perform_opcode(cw, cur_proc) != 0))
				return (code_error);
			opfork = (cur_proc->opcode == 12 || cur_proc->opcode == 15) ? 1 : 0;
			vm_proc_mv_proc_pos(cw, cur_proc);
			// tool_print_processor(cur_proc, cur_proc->id);
			// ft_printf(" >>>>>>>>>><<<<<<<<<<\n");
			if (opfork == 1)
			{
				xplr = cw->process;
				cur_proc = (t_process*)(xplr->cnt);
				opfork = 0;
				vm_proc_mv_proc_pos(cw, cur_proc);
			}
			else
				xplr = xplr->next;
		}
		else
			xplr = xplr->next;
	}
	return (0);
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
		if (cur_proc->wait_cycles > 0)
			cur_proc->wait_cycles -= 1;
		xplr = xplr->next;
	}
}