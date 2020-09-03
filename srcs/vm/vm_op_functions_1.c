/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:04:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/03 15:19:33 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_alive
** Description:
**	[put some explanations here !]
** Remarks:
**	The instruction alive allow to increment the live counter of the process
**	and the number of lives of the different champions.
**	There is no encoding byte, thus the argument of type direct (even if it is
**	not a direct argument) is parse.
**	If the argument correspond to a champion id, the number of live of the
**	corresponding champion (cw->champ_lives[x]) is increased, and the nb of
**	lives made by the process also as long as the champ id is a correct one.
** Return:
**	0:	The instruction alive doesn't take any encoded byte, it doesn't matter.
*/

int		op_alive(t_cw *cw, t_process *proc)
{
	t_arg	v_arg;
	int		arg;

	op_arg_init(&v_arg, 0, 0);
	arg = get_arg_value(cw, proc, proc->i + 1, DIR_CODE);
	v_arg.arg[0] = arg;
	v_arg.type[0] = DIR_CODE;
	proc->n_lives++;
	cw->ctd_lives++;
	cw->tot_lives++;
	proc->last_live = cw->tot_cycle;
	if (live_for_a_champ(cw->lst_champs, -arg) == 1)
	{
		cw->last_champ = -arg;
		cw->champ_lives[-arg - 1]++;
	}
	if (cw->options->verbose == true)
		verbotab(cw, proc, v_arg);
	return (0);
}

/*
** Function: op_load
** Description:
**	[put some explanations here !]
** Return:
**	0:
*/

int		op_load(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	t_arg		v_arg;
	int			arg[2];

	op_arg_init(&v_arg, 0, 0);
	arg[0] = get_arg_value(cw, p, p->i + 2, \
		((cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6) + RELATIVE);
	v_arg.arg[0] = arg[0];
	v_arg.type[0] = DIR_CODE;
	arg[1] = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	arg[1] = get_arg_value(cw, p, p->i + 2 + arg[1], REG_CODE);
	v_arg.arg[1] = arg[1];
	v_arg.type[1] = REG_CODE;
	p->carry = (arg[0] == 0) ? 1 : 0;
	p->registers[arg[1] - 1] = arg[0];
	if (cw->options->verbose == true)
		verbotab(cw, p, v_arg);
	return (0);
}

/*
** Function: op_store
** Description:
**	- Writes in
**	  cur_proc->registers[ARG_2] 						if type(ARG_2) == T_REG
**	  cw->arena[(index + (ARG_2 % IDX_MOD)) % MEM_SIZE] if type(ARG_2) == T_IND
**	  the value
**	  cur_proc->registers[ARG_1]
** Return:
**	0:
*/

int		op_store(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	t_arg		v_arg;
	int			arg[3];

	op_arg_init(&v_arg, REG_CODE, 3);
	arg[0] = get_arg_value(cw, p, p->i + 2, REG_CODE + RELATIVE);
	v_arg.arg[0] = get_arg_value(cw, p, p->i + 2, REG_CODE);
	arg[1] = get_arg_value(cw, p, p->i + 3, (((cw->arena[(p->i + 1) \
		% MEM_SIZE]) & 0b00110000) >> 4));
	v_arg.arg[1] = arg[1];
	if (((cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4) == IND_CODE)
	{
		v_arg.type[1] = DIR_CODE;
		arg[1] = p->i + (arg[1] % IDX_MOD);
		arg[1] = (arg[1] < 0) ? MEM_SIZE + arg[1] : arg[1];
		cw->arena[arg[1] % MEM_SIZE] = (arg[0] & 0xFF000000) >> 24;
		arg[2] = 0;
		while (++arg[2] < 4)
			cw->arena[(arg[1] + arg[2]) % MEM_SIZE] = (unsigned char)((arg[0] \
				& (0xFF000000 >> (8 * arg[2]))) >> (24 - 8 * arg[2]));
	}
	else
		p->registers[arg[1] - 1] = arg[0];
	(cw->options->verbose == true) ? verbotab(cw, p, v_arg) : 0;
	return (0);
}

/*
** Function: op_addition
** Description:
**	- Writes in cur_proc->registers[ARG_3] the value
**	  cur_proc->registers[ARG_1] + cur_proc->registers[ARG_2]
**	- cur->carry = 1 (if value == 0)
**				   0 (else)
** Return:
**	0: if encoding byte and arguments are valid.
**	-1: otherwise.
*/

int		op_addition(t_cw *cw, t_process *p)
{
	t_arg		v_arg;

	op_arg_init(&v_arg, REG_CODE, 7);
	v_arg.arg[0] = cw->arena[(p->i + 2) % MEM_SIZE];
	v_arg.arg[1] = cw->arena[(p->i + 3) % MEM_SIZE];
	v_arg.arg[2] = cw->arena[(p->i + 4) % MEM_SIZE];
	p->registers[v_arg.arg[2] - 1] = p->registers[v_arg.arg[0] - 1] \
		+ p->registers[v_arg.arg[1] - 1];
	p->carry = (p->registers[v_arg.arg[2] - 1] == 0) ? 1 : 0;
	if (cw->options->verbose == true)
		verbotab(cw, p, v_arg);
	return (0);
}
