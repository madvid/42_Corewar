/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 14:10:27 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/21 18:57:53 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: instruction_width
** Description:
**	[put some explanations here]
** Return
**	width: total length in term of bytes of the different parameters of opcode.
**	0: if the encoding byte is invalid.
*/
int		instruction_width(char encoding)
{
	[put the code].
}

/*
** Function: is_opcode
** Description:
**	[put some explanations here]
** Return:
**	1: if the byte is an opcode.
**	0: if the byte does not correspond to an opcode.
*/
bool	is_opcode(char byte)
{
	[put the code].
}

/*
** Function: addr_next_opcode
** Description:
**	Gets the address of the next opcode, without distinguish if the opcode is
**	related to the 'current' champion.
** Return:
**	addr: address of the next opcode.
**	NULL: there is no next opcode right after the ongoing one.
*/

void	*addr_next_opcode(char *arena, int mem_pos)
{
	char	encoding;
	int		addr_jump;

	encoding = arena[mem_pos + 1];
	addr_jump = instruction_width(encoding);
	if (!is_opcode(arena[mem_pos + 1 + addr_jump]))
		return (NULL);
	else
		return (&arena[mem_pos + 1 + addr_jump]);
}

/*
** Function: vm_exec_init_pc
** Description:
**	Initiates the very first processes of the champions, i.e. charging the 1st
**	instruction, storing the adress of the next opcode of each champion, sets
**	the wait_cycles and jump.
*/

static void		vm_exec_init_pc(t_cw *cw)
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
	//int			i_cycle;
	static bool	run_game;

	printf("valeur de run_game = %d\n", run_game);
	vm_exec_init_pc(cw);
	/*while (run_game == true)
	{
		i_cycle = -1;
		while (++i_cycle < cw->cycle_to_die)
		{
			...
		}
		// perform the different checks.
	}*/
	return (1); // <- changer le num par l'id du champion vainqueur.
}