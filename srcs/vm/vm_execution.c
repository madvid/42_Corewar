/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 14:10:27 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/18 09:52:50 by mdavid           ###   ########.fr       */
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
int		instruction_width(unsigned char encoding, size_t dir_s)
{
	u_int8_t	arg_1;
	u_int8_t	arg_2;
	u_int8_t	arg_3;
	size_t		size_dir;
	int			width;

	width = 0;
	size_dir = (dir_s == 1) ? 2 : 4;
	// printf("    [instruction_width] valeur de encoding = %d\n", (int)encoding);
	arg_1 = (encoding & 0b11000000) >> 6;
	arg_2 = (encoding & 0b00110000) >> 4;
	arg_3 = (encoding & 0b00001100) >> 2;
	// printf("[instruction_width]: arg1 = %d\n", arg_1);
	// printf("[instruction_width]: arg2 = %d\n", arg_2);
	// printf("[instruction_width]: arg3 = %d\n", arg_3);
	if (arg_1 != 0)
		width += size_dir * (arg_1 / 2) - 2 * (arg_1 / 3) + (1 - arg_1 / 2);
	// printf("[instruction_width]: width = %d\n", width);
	if (arg_2 != 0)
		width += size_dir * (arg_2 / 2) - 2 * (arg_2 / 3) + (1 - arg_2 / 2);
	// printf("[instruction_width]: width = %d\n", width);
	if (arg_3 != 0)
		width += size_dir * (arg_3 / 2) - 2 * (arg_3 / 3) + (1 - arg_3 / 2);
	// printf("[instruction_width]: width = %d\n", width);
	// printf("    [instruction_width] valeur de width = %d\n", width);
	return (width);
}



/*
** Function: vm_exec_init_pc
** Description:
**	Initiates the very first processes of the champions, i.e. charging the 1st
**	instruction, storing the adress of the next opcode of each champion, sets
**	the wait_cycles and jump.
*/

void		vm_exec_init_pc(t_cw *cw)
{
	extern t_op	op_tab[17];
	t_list		*l_xplr;
	t_process	*p_xplr;

	l_xplr = cw->process;
	while (l_xplr)
	{
		p_xplr = (t_process*)l_xplr->cnt;
		p_xplr->opcode = cw->arena[p_xplr->champ->mem_pos];
		p_xplr->wait_cycles = op_tab[p_xplr->opcode - 1].cycle;
		p_xplr->pc = addr_next_opcode(cw->arena, p_xplr->champ->mem_pos);
		l_xplr = l_xplr->next;
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

	score = cw->champ_lives[0];
	winner = 1;
	if (cw->champ_lives[1] > score)
	{
		score = cw->champ_lives[1];
		winner = 2;
	}
	if (cw->champ_lives[2] > score)
	{
		score = cw->champ_lives[2];
		winner = 3;
	}
	if (cw->champ_lives[3] > score)
	{
		score = cw->champ_lives[3];
		winner = 4;
	}
	name = champ_name_via_id(cw->lst_champs, winner);
	ft_printf("Contestant %d, %c%s%c, has won !", winner, '"', name, '"');
	return (1);
}

/*
** Function: vm_execution
** Description:
**	Main part of the execution of the champion bytecode [bla bla]
** Return:
**	0: No error or issue occured.
**	code_error: value of the corresponding error/issue which occured
**
*/

int		vm_execution(t_cw *cw, t_parse * p)
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
			vm_proc_mv_proc_pos(cw);
			vm_proc_cycle(cw);
			if (cw->options->v_lvl & 2 && cw->i_cycle != 0)
				vprint_cycle(cw, NULL, 0);
			if (cw->options->dump && cw->tot_cycle == cw->options->dump_cycle)
				return (dump_memory(cw->arena));
			if ((code_error = vm_proc_perform_opcode(cw)) != 0)
				return (code_error);
			cw->tot_cycle++;
		}
		//vm_proc_get_lives(cw); <- augmentation de cw->tot_lives/ctd_lives pendant l'action alive, peut etre retiré donc.
		// if (cw->ctd_lives == 0 || !vm_proc_only_one_standing(cw))
		if (cw->ctd_lives == 0 || cw->process == NULL)
			stop_game = true;
		if (cw->i_check++ == MAX_CHECKS || cw->ctd_lives >= NBR_LIVE)
		{
			cw->cycle_to_die -= (int)CYCLE_DELTA;
			cw->i_check = (cw->i_check == MAX_CHECKS) ? 0 : cw->i_check;
			if (cw->options->v_lvl & 2)
			{
				vprint_cycle(cw, NULL, 1);
				// vprint_cycle(cw, NULL, 0);
			}
		}
		if (vm_proc_kill_not_living(cw) == 0 || cw->cycle_to_die <= 0)
			return (declare_winner(cw));
		vm_proc_set_lives(cw, 0);
	}
	p = NULL;
	//tool_print_arena(cw->arena, (size_t)MEM_SIZE, p);
	return (0); // <- changer le num par l'id du champion vainqueur ? ou alors faire gérer la fin par only_one_standing.
}