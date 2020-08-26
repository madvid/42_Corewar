/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 14:10:27 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/26 15:51:17 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: instruction_width
** Description:
**	Reads the encoding byte and calculates the length in bytes of the arguments
**	field.
** Remarks:
**	Each arg can take 4 values:
**		arg_1: can be 192/128/64 depending if 11/10/01 (xx 00 00 00).
**		arg_2: can be 48/32/16 depending if 11/10/01 (00 xx 00 00).
**		arg_3: can be 12/8/4 depending if 11/10/01 (00 00 xx 00).
** Reminder:
**	In the encoding byte are present the type of the different arguments:
**		11 means the argument is an indirect type (2 bytes long),
**		10 means the argument is an direct type (4 bytes long),
**		01 means the argument is an indirect type (1 byte long)
** Return
**	width: total length in term of bytes of the different parameters of opcode.
**	0: if the encoding byte is invalid.
*/

int		instruction_width(unsigned char encoding, t_op op_elem)
{
	u_int8_t	arg_1;
	u_int8_t	arg_2;
	u_int8_t	arg_3;
	size_t		size_dir;
	int			width;

	width = 0;
	size_dir = (op_elem.direct_size == 1) ? 2 : 4;
	arg_1 = (encoding & 0b11000000) >> 6;
	arg_2 = (encoding & 0b00110000) >> 4;
	arg_3 = (encoding & 0b00001100) >> 2;
	if (arg_1 != 0 && op_elem.n_arg >= 1)
		width += (arg_1 == 2) ? size_dir : 2 * (arg_1 / 3) + (1 - arg_1 / 2);
	if (arg_2 != 0 && op_elem.n_arg >= 2)
		width += (arg_2 == 2) ? size_dir : 2 * (arg_2 / 3) + (1 - arg_2 / 2);
	if (arg_3 != 0 && op_elem.n_arg >= 3)
		width += (arg_3 == 2) ? size_dir : 2 * (arg_3 / 3) + (1 - arg_3 / 2);
	return (width);
}

/*
** Function: vm_exec_init_pc
** Description:
**	Initiates the very first processes of the champions, i.e. charging the 1st
**	instruction, storing the adress of the next opcode of each champion, sets
**	the wait_cycles and jump.
*/

void	vm_exec_init_pc(t_cw *cw)
{
	extern t_op	op_tab[17];
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
	int		score;
	int		winner;
	char	*name;
	int		i;

	score = cw->champ_lives[0];
	winner = 1;
	i = 1;
	while (i < 4)
	{
		if (cw->champ_lives[i] > score)
		{
			score = cw->champ_lives[i];
			winner = i + 1;
		}
		i++;
	}
	name = champ_name_via_id(cw->lst_champs, winner);
	ft_printf("Contestant %d, %c%s%c, has won !", winner, '"', name, '"');
	return (1);
}

/*
** Function: new_attribut_proc
** Description:
**	Attributes to the process the value of the opcode at the position proc->i
**	in the arena.
**	If the opcode value is invalid (not in [1;16]), wait_cycles is set to 1
**	otherwise it is set to the corresponding value in op_tab (see op.c).
*/

void	new_attribut_proc(t_cw *cw, t_process *proc)
{
	extern t_op		op_tab[17];

	if (proc->wait_cycles == -1)
	{
		proc->opcode = cw->arena[proc->i];
		if (proc->opcode >= 1 && proc->opcode <= 16)
			proc->wait_cycles = op_tab[proc->opcode - 1].cycle;
		else
			proc->wait_cycles = 1;
	}
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

	xplr = cw->process;
	if (cw->options->v_lvl & 2 && cw->i_cycle != 0)
		vprint_cycle(cw, NULL, op_arg(0, (t_process*)(xplr), 0, 0, 0), 0);
	while (xplr)
	{
		proc = (t_process*)(xplr->cnt);
		new_attribut_proc(cw, proc);
		proc->wait_cycles--;
		code_error = vm_proc_perform_opcode(cw, proc);
		xplr = xplr->next;
	}
	if (cw->options->dump && cw->tot_cycle == cw->options->dump_cycle)
		return (dump_memory(cw->arena));
	return (0);
}

/*
** Function: ctd_control
** Description:
**	Checks if the parameter Cycle_To_Died (ctd) must be decreased.
**	Two cases can be distinguished:
**	* total nb of lives during the 'current period' > NBR_LIVE,
**	* cycle_to_die hasn't be decrease since MAX_CHECKS verification.
*/

void	ctd_control(t_cw *cw)
{
	if (cw->i_check++ == MAX_CHECKS || cw->ctd_lives >= NBR_LIVE)
	{
		cw->cycle_to_die -= (int)CYCLE_DELTA;
		cw->i_check = (cw->i_check == MAX_CHECKS) ? 0 : cw->i_check;
		if (cw->options->v_lvl & 2)
			vprint_cycle(cw, NULL, op_arg(0, (t_process*)(cw->process), 0, 0, 0),  1);
		if (cw->cycle_to_die < 0)
			vprint_cycle(cw, NULL, op_arg(0, (t_process*)(cw->process), 0, 0, 0), 0);
	}
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
	vm_exec_init_pc(cw);
	cw->tot_cycle = 1;
	while (stop_game == false)
	{
		cw->i_cycle = 0;
		cw->ctd_lives = 0;
		while (++cw->i_cycle <= cw->cycle_to_die)
		{
			if ((code_error = procedural_loop(cw)) != 0)
				return (code_error);
			cw->tot_cycle++;
		}
		if (vm_proc_kill_not_living(cw) == 0 || cw->cycle_to_die < 0)
			return (declare_winner(cw));
		ctd_control(cw);
		if (cw->ctd_lives == 0 || cw->process == NULL)
			stop_game = true;
		// vm_proc_set_lives(cw, 0);
	}
	return (0);
}
