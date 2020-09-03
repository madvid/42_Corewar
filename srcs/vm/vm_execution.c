/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 14:10:27 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/03 16:56:27 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: vm_init_wcycle
** Description:
**	Initiates the very first processes of the champions, i.e. charging the 1st
**	instruction, storing the adress of the next opcode of each champion, sets
**	the wait_cycles and jump.
*/

void	vm_init_wcycle(t_cw *cw)
{
	t_list		*xplr;
	t_process	*proc;

	xplr = cw->process;
	while (xplr)
	{
		proc = (t_process*)xplr->cnt;
		proc->wait_cycles = -1;
		xplr = xplr->next;
	}
}

/*
** Function: declare_winner
** Description:
**	Declares the winner of the battle.
** Return:
**		1: battle reach the end without any problems
*/

int		declare_winner(t_cw *cw)
{
	char		*name;
	t_list		*xplr;

	if (cw->lst_champs == NULL)
		return (0);
	name = NULL;
	xplr = cw->lst_champs;
	while (xplr)
	{
		if (((t_champ*)(xplr->cnt))->id == cw->last_champ)
		{
			name = ((t_champ*)(xplr->cnt))->name;
			break ;
		}
		xplr = xplr->next;
	}
	if (!name)
		return (0);
	ft_printf("Contestant %d, \"%s\", has won !\n", cw->last_champ, name);
	return (FIN_DU_GAME);
}

/*
** Function: procedural_loop
** Description:
**	Performs the loop on the processes.
**	More specifically, it go through all the processes and makes:
**	* the attributions of the opcode and wait_cycles,
**	* performs the instructions and get the next pc,
**	* deals the dump option.
** Return:
**	0: If no error has been encounter,
**	code_error: code of the error encounters.
*/

int		procedural_loop(t_cw *cw)
{
	int			code_error;
	t_list		*xplr;
	t_process	*proc;

	code_error = 0;
	if (cw->options->v_lvl & 2)
		vprint_cycle(cw, 1);
	xplr = cw->process;
	while (xplr)
	{
		proc = (t_process*)(xplr->cnt);
		if (proc->wait_cycles == -1)
		{
			proc->opcode = cw->arena[proc->i];
			proc->wait_cycles = (proc->opcode >= 1 && proc->opcode <= 16) \
				? cw->op_tab[proc->opcode - 1].cycle : 1;
		}
		proc->wait_cycles--;
		if ((code_error = vm_proc_perform_opcode(cw, proc)) > 0)
			return (code_error);
		xplr = xplr->next;
	}
	if (cw->options->dump && cw->tot_cycle == cw->options->dump_cycle)
		return (dump_memory(cw->arena));
	return (code_error);
}

/*
** Function: ctd_control
** Description:
**	Checks if the parameter Cycle_To_Died (ctd) must be decreased.
**	Two cases can be distinguished:
**	* total nb of lives during the 'current period' > NBR_LIVE,
**	* cycle_to_die hasn't be decrease since MAX_CHECKS verification.
*/

int		ctd_control(t_cw *cw)
{
	int			code_error;

	if (++cw->i_check == MAX_CHECKS || cw->ctd_lives > NBR_LIVE)
	{
		cw->cycle_to_die -= (int)CYCLE_DELTA;
		cw->i_check = (cw->i_check == MAX_CHECKS) ? 0 : cw->i_check;
		if (cw->options->v_lvl & 2)
			vprint_cycle(cw, 0);
		if (cw->cycle_to_die < 1)
		{
			if ((code_error = procedural_loop(cw)) > 0)
				return (code_error);
			if (vm_proc_kill_not_living(cw) == 0)
				return (declare_winner(cw));
		}
	}
	return (0);
}

/*
** Function: vm_execution
** Description:
**	Main part of the VM execution
**	* Initialization of the primary processes,
**	* Proceeding of the 'temporal' loop and run of the procedural loop.
**	* Control of the Cycle_To_Die parameter,
**	* Managment of the supression of died processes,
**	* Reset of the number of live realized by the whole processes.
** Return:
**	0: No error or issue occured.
**	code_error: value of the corresponding error/issue which occured
*/

int		vm_execution(t_cw *cw)
{
	static bool	stop_game;
	int			code_error;

	code_error = 0;
	vm_init_wcycle(cw);
	cw->tot_cycle = 1;
	if (cw->options->dump && cw->options->dump_cycle == 0)
		return (dump_memory(cw->arena));
	while (stop_game == false)
	{
		cw->i_cycle = 0;
		cw->ctd_lives = 0;
		while (++cw->i_cycle <= cw->cycle_to_die)
		{
			if ((code_error = procedural_loop(cw)) > 0)
				return (code_error);
			cw->tot_cycle++;
		}
		if (vm_proc_kill_not_living(cw) == 0 || cw->cycle_to_die < 0)
			return (declare_winner(cw));
		ctd_control(cw);
		if (cw->ctd_lives == 0 || cw->process == NULL)
			stop_game = true;
	}
	return (FIN_DU_GAME);
}
