/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:41:23 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/23 18:37:13 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

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
		while (++i < REG_NUMBER)
			ft_strdel(&(((t_process*)(xplr->cnt))->registers[i]));
		free(((t_process*)(xplr->cnt))->registers);
		free(xplr->cnt);
		free(xplr);
	}
	else
	{
		while (xplr->next && ((t_process*)((xplr)->next->cnt))->id != id)
			xplr = xplr->next;
		to_del = xplr->next;
		xplr->next = xplr->next->next;
		while (++i < REG_NUMBER)
			ft_strdel(&(((t_process*)(to_del->cnt))->registers[i]));
		free(((t_process*)(to_del->cnt))->registers);
		((t_process*)(to_del->cnt))->registers = NULL;
		free(to_del->cnt);
		to_del->cnt = NULL;
		free(to_del);
		to_del = NULL;
	}
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
** Function: vm_proc_perform_opcode
** Description:
**	[put some explanations !]
** Return:
**	1: action of the opcode have been performed, for all processes.
**	0: Something wrong happen [find what wrong could happen].
*/

/*int		vm_proc_perform_opcode(t_cw *cw)
{
	t_list		*xplr;
	t_process	*cur_proc;

	xplr = cw->process;
	while (xplr)
	{
		xplr = xplr->next;
	}
	return (1);
}*/

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