/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_process2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 16:34:01 by armajchr          #+#    #+#             */
/*   Updated: 2020/09/04 13:20:20 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


static void	vm_p_kill_verbo(t_cw *cw, t_list *xplr)
{
	if (cw->options->v_lvl & 0b00001000)
		vprint_deaths(cw, (t_process*)(xplr->cnt));
}

static void	vm_kill_else(t_cw *cw, t_list **before, t_list *next, t_list **xplr)
{
	if (*xplr - cw->process == 0)
	{
		cw->process = next;
		*before = next;
	}
	else
		(*before)->next = next;
}

/*
** Function: vm_proc_kill_no_live
** Description:
**	"Normalement ça marche"
** Return:
**	1: if at least one process remaind in the list cw->process after killing
**		concerned processes.
**	0: if no process remainds or if the number of processes exceed INT_MAX
*/

int			vm_proc_kill_not_living(t_cw *cw)
{
	t_list		*xplr;
	t_list		*next;
	t_list		*before;

	xplr = cw->process;
	while (xplr)
	{
		next = xplr->next;
		((t_process*)(xplr->cnt))->n_lives = 0;
		if (cw->tot_cycle - ((t_process*)(xplr->cnt))->last_live \
			+ ((cw->cycle_to_die > 0) ? -1 : 0) >= cw->cycle_to_die)
		{
			vm_p_kill_verbo(cw, xplr);
			vm_kill_else(cw, &before, next, &xplr);
			ft_lstdelone(&xplr, &ft_lst_fdel_proc);
		}
		else
			before = xplr;
		xplr = next;
	}
	return ((ft_lst_len(cw->process) == 0) ? 0 : 1);
}

