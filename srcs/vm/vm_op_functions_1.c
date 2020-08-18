/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:04:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/17 18:58:39 by mdavid           ###   ########.fr       */
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
**	1:	the instruction is valid (= encoding byte coherent) or no encoding byte
**		needed by the instruction thus it is performed in any case.
**	0:	if the encoding byte is not coherent with what the instruction takes
**		as argument(s).
*/

int		op_alive(t_cw *cw, t_process *proc)
{
	int		arg;

	arg = get_arg_value(cw->arena, proc, proc->i + 1, DIR_CODE);
	proc->n_lives++;
	cw->ctd_lives++;
	cw->tot_lives++;
	proc->last_live = cw->i_cycle;
	if (-arg > 0 && -arg < cw->n_champ)
		cw->champ_lives[-arg - 1]++;
	return ((cw->options->verbose == true) ? init_verbotab(cw, proc, -arg) : 1);
}

/*
** Function: op_load
** Description:
**	[put some explanations here !]
** Return:
**	1:
**	0:
*/

int		op_load(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	int			arg;
	int			reg;

	//arg = get_arg_value(cw->arena, p, p->i + 2, (((cw->arena[(p->i + 1) \
	//	% MEM_SIZE]) & 0b11000000) >> 6) + RELATIVE);
	arg = get_arg_value(cw->arena, p, p->i + 2, (((cw->arena[(p->i + 1) \
		% MEM_SIZE]) & 0b11000000) >> 6) + RELATIVE);
	reg = instruction_width((cw->arena[(p->i + 1) \
		% MEM_SIZE]) & 0b11000000, op_tab[p->opcode - 1].direct_size);
	reg = get_arg_value(cw->arena, p, p->i + 2 + reg, \
		((cw->arena[(p->i + 1) % MEM_SIZE]) & 0b00110000) >> 4);
	p->carry = (arg == 0) ? 1 : 0;
	p->registers[reg - 1] = arg;
	return ((cw->options->verbose == true) ? init_verbotab(cw, p, 1) : 1);
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
	int		a;
	int		b;
	int		i;

	(cw->options->verbose == true) ? init_verbotab(cw, p, 1) : 1;
	a = cw->arena[(p->i + 2) % MEM_SIZE];
	b = cw->arena[(p->i + 3) % MEM_SIZE];
	if (((cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4) == IND_CODE)
	{
		b = (b << 8) | (u_int8_t)(cw->arena[(p->i + 4) % MEM_SIZE]);
		// ft_printf("    [op_store]: 1er arg = %d\n", a);
		// ft_printf("    [op_store]: 2nd arg = %d\n", b);
		i = -1;
		while (++i < 4)
		{
			cw->arena[(p->i + (b % IDX_MOD) + i) % MEM_SIZE] \
			= (p->registers[a - 1] & (0xFF000000 >> (8 * i))) >> (24 - 8 * i);
		}
	}
	else
		p->registers[b - 1] = p->registers[a - 1];
	// else if (((cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4) == REG_CODE)
	// 	p->registers[b - 1] = p->registers[a - 1];
	// else
	// 	return ((cw->options->verbose == true) ? vprint_op(cw, (void*)p, 0) : 0);
	return (1);
}

/*
** Function: op_addition
** Description:
**	- Writes in cur_proc->registers[ARG_3] the value
**	  cur_proc->registers[ARG_1] + cur_proc->registers[ARG_2]
**	- cur->carry = 1 (if value == 0)
**				   0 (else)
** Return:
**	[value_1]: 1 if encoding byte and arguments are valid
**	[value_2]: 0 else
*/

int		op_addition(t_cw *cw, t_process *cur_proc)
{
	int		a;
	int		b;
	int		c;
	int		i;

	a = cw->arena[(cur_proc->i + 2) % MEM_SIZE];
	b = cw->arena[(cur_proc->i + 3) % MEM_SIZE];
	c = cw->arena[(cur_proc->i + 4) % MEM_SIZE];
	if (a < 1 || a > REG_NUMBER || b < 1 || b > REG_NUMBER \
		|| c < 1 || c > REG_NUMBER)
		return (i = (cw->options->verbose == true) ? init_verbotab(cw, cur_proc, 0) : 0);
	cur_proc->registers[c - 1] = cur_proc->registers[a - 1] \
	+ cur_proc->registers[b - 1];
	cur_proc->carry = (cur_proc->registers[c - 1] == 0) ? 1 : 0;
	return (i = (cw->options->verbose == true) ? init_verbotab(cw, cur_proc, 1) : 1);
}
