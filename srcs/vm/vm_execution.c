/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 14:10:27 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/28 15:49:49 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: reconstruct_arg_width
** Description:
**	[put some explanations here]
** Return:
**	len: the minimal value of the arguments length field.
*/

int		reconstruct_arg_width(int opcode)
{
	int		len;

	len = 0;
	
	return (len)
}

/*
** Function: min_arg_width
** Description:
**	[put some explanations here]
** Return:
**	len: the minimal value of the arguments length field.
*/

int		min_arg_width(u_int8_t opcode)
{
	int		len;

	len = 0;
	
	return (len)
}

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
		p_xplr->n_lives = p_xplr->id - 1; // to suppress
		l_xplr = l_xplr->next;
	}
}

/*
** Function: vm_execution
** Description:
**	Main part of the execution of the champion bytecode [bla bla]
** Return:
**	winner_id : id of the champion who won the battle
**	0: if any problem has occured.
*/

int		vm_execution(t_cw *cw)
{
	int			i_cycle;
	static bool	stop_game;

	vm_exec_init_pc(cw);
	cw->cycle_to_die = 100; // to supress
	while (stop_game == false)
	{
		i_cycle = -1;
		while (++i_cycle < cw->cycle_to_die)
		{
			printf(">>> i_cycle = %d\n", i_cycle);
			vm_proc_cycle(cw);
			vm_proc_perform_opcode(cw);
			vm_proc_mv_proc_pos(cw);
		}
		// ICI ajouter une fonction qui va attribuer une valeur a cw->lives + retirer les processus qui n'ont pas live pendant cw->cycle_to_die cycle
		cw->tot_lives = vm_proc_get_lives(cw);
		vm_proc_kill_not_living(cw);
		if (cw->tot_lives == 0 || !vm_proc_only_one_standing(cw))
			stop_game = true;
		break ; // to suppress;
		vm_proc_set_lives(cw, 0);
		if (cw->tot_lives >= NBR_LIVE)
			cw->cycle_to_die -= (int)CYCLE_DELTA;
	}
	return (1); // <- changer le num par l'id du champion vainqueur ? ou alors faire gérer la fin par only_one_standing.
}