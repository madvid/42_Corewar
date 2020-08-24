/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 14:10:27 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/24 17:08:46 by mdavid           ###   ########.fr       */
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

void		vm_exec_init_pc(t_cw *cw)
{
	extern t_op	op_tab[17];
	t_list		*l_xplr;
	t_process	*p_xplr;

	l_xplr = cw->process;
	while (l_xplr)
	{
		p_xplr = (t_process*)l_xplr->cnt;
		// p_xplr->opcode = cw->arena[p_xplr->champ->mem_pos];
		// p_xplr->wait_cycles = op_tab[p_xplr->opcode - 1].cycle;
		p_xplr->wait_cycles = -1;
		// ------> Initial
		//p_xplr->pc = addr_next_opcode(cw->arena, p_xplr->champ->mem_pos);
		// ------> proposition 1
		// p_xplr->pc = addr_next_opcode(cw->arena, p_xplr);
		// ------> proposition 2
		// p_xplr->pc = p_xplr->i + instruction_width((p_xplr->i + 1) % MEM_SIZE, \
		// 	op_tab[p_xplr->opcode - 1]); // ne marche pas bien si le champion ne commence pas par une instruction valide je pense.
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

static void		new_attribut_proc(t_cw *cw, t_process *proc)
{
	extern t_op		op_tab[17];
	
	if (proc->wait_cycles == -1)
	{
		proc->opcode = cw->arena[proc->i];
		if (proc->opcode >= 1 && proc->opcode <= 16)
			proc->wait_cycles = op_tab[proc->opcode - 1].cycle;
		else
			proc->wait_cycles = 1;
		// proc->pc = addr_next_opcode(cw->arena, proc);
	}
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

int		vm_execution(t_cw *cw, t_parse *p)
{
	static bool	stop_game;
	int			code_error;
	t_list		*xplr;
	t_process	*proc;

	code_error = 0;
	vm_exec_init_pc(cw);
	cw->tot_cycle = 1;
	while (stop_game == false)
	{
		cw->i_cycle = 0;
		cw->ctd_lives = 0;
		while (++cw->i_cycle <= cw->cycle_to_die)
		{
			if (cw->options->v_lvl & 2 && cw->i_cycle != 0)
				vprint_cycle(cw, NULL, 0);
			xplr = cw->process;
			while (xplr)
			{
				proc = (t_process*)(xplr->cnt);
				new_attribut_proc(cw, proc);
				proc->wait_cycles--;
				vm_proc_perform_opcode(cw, proc);
				xplr = xplr->next;
			}
			if (cw->options->dump && cw->tot_cycle == cw->options->dump_cycle)
				return (dump_memory(cw->arena));
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
