/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 14:10:27 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/22 18:24:15 by mdavid           ###   ########.fr       */
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
int		instruction_width(unsigned char encoding)
{
	u_int8_t	arg_1;
	u_int8_t	arg_2;
	u_int8_t	arg_3;
	int			width;

	width = 0;
	// printf("    [instruction_width] valeur de encoding = %d\n", (int)encoding);
	arg_1 = (encoding & 0b11000000) >> 6;
	arg_2 = (encoding & 0b00110000) >> 4;
	arg_3 = (encoding & 0b00001100) >> 2;
	if (arg_1 != 0)
		width += 4 * (arg_1 / 2) - 2 * (arg_1 / 3) + (1 - arg_1 / 2);
	if (arg_2 != 0)
		width += 4 * (arg_2 / 2) - 2 * (arg_2 / 3) + (1 - arg_2 / 2);
	if (arg_3 != 0)
		width += 4 * (arg_3 / 2) - 2 * (arg_3 / 3) + (1 - arg_3 / 2);
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
	bool		run_game;

	vm_exec_init_pc(cw);
	run_game = true;
	while (run_game == true)
	{
		i_cycle = -1;
		/*while (++i_cycle < cw->cycle_to_die)
		{
			...
		}*/
		// ICI ajouter une fonction qui va attribuer une valeur a cw->lives + retirer les processus qui n'ont pas live pendant cw->cycle_to_die cycle
		if (cw->nb_lives >= NBR_LIVE)
			cw->cycle_to_die -= (int)CYCLE_DELTA;
		if (cw->nb_lives == 0)
			run_game = false;
	}
	return (1); // <- changer le num par l'id du champion vainqueur.
}