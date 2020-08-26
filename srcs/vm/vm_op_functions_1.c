/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:04:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/27 01:46:06 by mdavid           ###   ########.fr       */
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
	int		arg;

	arg = get_arg_value(cw->arena, proc, proc->i + 1, DIR_CODE);
	proc->n_lives++;
	cw->ctd_lives++;
	cw->tot_lives++;
	proc->last_live = cw->tot_cycle;
	if (-arg > 0 && -arg < cw->n_champ)
		cw->champ_lives[-arg - 1]++;
	if (cw->options->verbose == true)
		verbotab(cw, proc, op_arg(0, proc, arg, 0, 0));
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
	int			arg;
	u_int8_t	encod;
	int			reg;

	encod = cw->arena[(p->i + 1) % MEM_SIZE];
	arg = get_arg_value(cw->arena, p, p->i + 2, \
		((encod & 0b11000000) >> 6) + RELATIVE);
	reg = instruction_width(encod & 0b11000000, op_tab[p->opcode - 1]);
	reg = get_arg_value(cw->arena, p, p->i + 2 + reg, \
		(encod & 0b00110000) >> 4);
	p->carry = (arg == 0) ? 1 : 0;
	p->registers[reg - 1] = arg;
	if (cw->options->verbose == true)
	{
		tool_print_t_arg(op_arg(encod, p, arg, reg, 0));
		verbotab(cw, p, op_arg(encod, p, arg, reg, 0));
	}
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
**	[value_1]: 1 if encoding byte and arguments are valid
**	[value_2]: 0 else
*/

int		op_store(t_cw *cw, t_process *p)
{
	int			a;
	int			b;
	int			i;
	extern t_op	op_tab[17];

	a = get_arg_value(cw->arena, p, p->i + 2, (((cw->arena[(p->i + 1) \
		% MEM_SIZE]) & 0b11000000) >> 6) + RELATIVE);
	b = get_arg_value(cw->arena, p, p->i + 3, (((cw->arena[(p->i + 1) \
		% MEM_SIZE]) & 0b00110000) >> 4));
	cw->options->v_p = 1;
	if (((cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4) == IND_CODE)
	{
		b = p->i + (b % IDX_MOD);
		b = (b < 0) ? MEM_SIZE + b : b;
		if (cw->options->v_lvl & 4)
			vprint_op(p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE] + 20, p, a, b, 0));
		cw->arena[b % MEM_SIZE] = (a & 0xFF000000) >> 24;
		i = 0;
		while (++i < 4)
		{
			cw->arena[(b + i) % MEM_SIZE] = \
			(unsigned char)((a & (0xFF000000 >> (8 * i))) \
				>> (24 - 8 * i));
		}
	}
	else
		p->registers[b - 1] = a;
	if (cw->options->v_lvl & 16)
		vprint_pcmv(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, 0));
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
	int		a;
	int		b;
	int		c;

	a = cw->arena[(p->i + 2) % MEM_SIZE];
	b = cw->arena[(p->i + 3) % MEM_SIZE];
	c = cw->arena[(p->i + 4) % MEM_SIZE];
	if (a < 1 || a > REG_NUMBER || b < 1 || b > REG_NUMBER \
		|| c < 1 || c > REG_NUMBER)
		{
			verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, c));
			return (-1);
		}
	p->registers[c - 1] = p->registers[a - 1] \
	+ p->registers[b - 1];
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	if (cw->options->verbose == true)
		verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, c));
	return (0);
}
