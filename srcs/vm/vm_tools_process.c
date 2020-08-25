/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:41:23 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/25 16:14:23 by mdavid           ###   ########.fr       */
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
			// ((t_process*)(xplr->cnt))->id == 5074 ? tool_print_processor((t_process*)(xplr->cnt), 5074) : 0;
			next = xplr->next;
			if (cw->options->v_lvl & 0b1000)
				vprint_deaths(cw, (t_process*)(xplr->cnt), 1);
			// ft_lst_delone() avec lst_fdel_proc
			ft_lst_fdel_proc(xplr, xplr->cnt_s);
			before->next = next;
			xplr = next;
		}
		else
		{
			((t_process*)(xplr->cnt))->n_lives = 0;
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
** Function: vm_proc_perform_opcode
** Description:
**	[put some explanations !]
** Return:
**	code_error: value of the corresponding error
**	0: No error/issue occured
*/

int		vm_proc_perform_opcode(t_cw *cw, t_process *proc)
{
	int			code_error;

	code_error = 0;
	if (proc->wait_cycles == 0)
	{
		proc->pc = addr_next_opcode(cw->arena, proc);
		if ((code_error = perform_opcode(cw, proc) != 0))
			return (code_error);
		proc->i = proc->pc;
		proc->wait_cycles = -1;
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