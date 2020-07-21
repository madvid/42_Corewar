/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 14:10:27 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/21 18:22:21 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: 
** Description:
**
** Return:
*/

void	*get_next_opcode(char *arena, )
{
	return ();
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
		p_xplr->pc = get_next_opcode(cw->arena, p_xplr->champ->mem_pos);
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
	int		i_cycle;
	bool	run_game; 

	printf("valeur de run_game = %d\n", run_game)
	vm_exec_init_pc(cw);
	while (run_game == true)
	{
		i_cycle = -1;
		while (++i_cycle < cw->cycle_to_die)
		{
			...
		}
		// perform the different checks.
	}
	return (1); // <- changer le num par l'id du champion vainqueur.
}