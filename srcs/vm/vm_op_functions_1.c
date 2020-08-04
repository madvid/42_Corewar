/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:04:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/04 15:10:26 by mdavid           ###   ########.fr       */
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

int		op_alive(t_cw *cw, t_process *cur_proc)
{
	int		arg;

	printf("Alive en cours.\n");
	arg = (cw->arena[(cur_proc->i + 1) % MEM_SIZE] & 255) << 24
		| (cw->arena[(cur_proc->i + 2) % MEM_SIZE] & 255) << 16
		| (cw->arena[(cur_proc->i + 3) % MEM_SIZE] & 255) << 8
		| (cw->arena[(cur_proc->i + 4) % MEM_SIZE] & 255);
	cur_proc->n_lives++; // even if the arg contain a non valid champ id.
	if (arg > 0 && arg < cw->n_champ) // not sure for this, is alive instruction always valid as long as the argument is a positive int ? or in every case ?
	{
		cw->champ_lives[arg - 1]++;
		return (1);
	}
	return (1);
}

/*
** Function: op_load
** Description:
**	[put some explanations here !]
** Return:
**	1:
**	0:
*/

int		op_load(t_cw *cw, t_process *cur_proc)
{
	int			arg;
	u_int8_t	reg;
	extern t_op	op_tab[17];

	printf("Load instruction en cours\n");
	arg = get_arg_value(cw, cur_proc, cur_proc->i + 2, \
		(((cw->arena[(cur_proc->i + 1) % MEM_SIZE]) & 0b11000000) >> 6) + RELATIVE);
	reg = instruction_width(((cw->arena[(cur_proc->i + 1) % MEM_SIZE]) & 0b11000000), op_tab[cur_proc->opcode - 1].direct_size);
	printf("reg apres instruction width: %d\n", reg);
	reg = get_arg_value(cw, cur_proc, cur_proc->i + 2 + reg, \
		((cw->arena[(cur_proc->i + 1) % MEM_SIZE]) & 0b00110000) >> 4);
	printf("numero de registre ou ecrire: %d\n", reg);
	if (reg > REG_NUMBER || reg < 1)
		return (0);
	cur_proc->registers[reg - 1] = arg;
	cur_proc->carry = (arg == 0) ? 1 : 0;
	// printf("valeur du contenue du registre apres ecriture: %d\n", arg);
	return (1);
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

int		op_store(t_cw *cw, t_process *cur_proc)
{
	int			a;
	int			b;

	printf("Store instruction en cours\n");
	a = cw->arena[(cur_proc->i + 2) % MEM_SIZE];
	if (a < 1 || a > REG_NUMBER)
		return (0);
	b = cw->arena[(cur_proc->i + 3) % MEM_SIZE];
	if (((cw->arena[(cur_proc->i + 1) % MEM_SIZE] & 0b00110000) >> 4) == IND_CODE)
	{
		b = (b << 8) | cw->arena[(cur_proc->i + 4) % MEM_SIZE];
		// printf("     (cur_proc->i + (b %% IDX_MOD)) %% MEM_SIZE = %d\n", (cur_proc->i + (b % IDX_MOD)) % MEM_SIZE);
		// printf("     (cur_proc->i + ((b+1) %% IDX_MOD)) %% MEM_SIZE = %d\n", (cur_proc->i + ((b+1) % IDX_MOD)) % MEM_SIZE);
		// printf("     (cur_proc->i + ((b+2) %% IDX_MOD)) %% MEM_SIZE = %d\n", (cur_proc->i + ((b+2) % IDX_MOD)) % MEM_SIZE);
		// printf("     (cur_proc->i + ((b+3) %% IDX_MOD)) %% MEM_SIZE = %d\n", (cur_proc->i + ((b+3) % IDX_MOD)) % MEM_SIZE);
		// printf("     (cur_proc->registers[a - 1] & 4278190080) >> 24 = %lX\n", (cur_proc->registers[a - 1] & 4278190080) >> 24);
		// printf("     (cur_proc->registers[a - 1] & 16711680) >> 16 = %X\n", (cur_proc->registers[a - 1] & 16711680) >> 16);
		// printf("     (cur_proc->registers[a - 1] & 65280) >> 8 = %X\n", (cur_proc->registers[a - 1] & 65280) >> 8);
		// printf("     (cur_proc->registers[a - 1] & 255) = %X\n", (cur_proc->registers[a - 1] & 255));
		cw->arena[(cur_proc->i + (b % IDX_MOD)) % MEM_SIZE] = (cur_proc->registers[a - 1] & 4278190080) >> 24;
		cw->arena[(cur_proc->i + ((b + 1) % IDX_MOD)) % MEM_SIZE] = (cur_proc->registers[a - 1] & 16711680) >> 16;
		cw->arena[(cur_proc->i + ((b + 2) % IDX_MOD)) % MEM_SIZE] = (cur_proc->registers[a - 1] & 65280) >> 8;
		cw->arena[(cur_proc->i + ((b + 3) % IDX_MOD)) % MEM_SIZE] = (cur_proc->registers[a - 1] & 255);
	}
	else if (((cw->arena[(cur_proc->i + 1) % MEM_SIZE] & 0b00110000) >> 4) == REG_CODE \
		&& b > 0 && b <= REG_NUMBER)
		cur_proc->registers[b - 1] = cur_proc->registers[a - 1];
	else
		return (0);
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

	a = cw->arena[(cur_proc->i + 2) % MEM_SIZE];
	b = cw->arena[(cur_proc->i + 3) % MEM_SIZE];
	c = cw->arena[(cur_proc->i + 4) % MEM_SIZE];
	if (a < 1 || a > REG_NUMBER || b < 1 || b > REG_NUMBER \
		|| c < 1 || c > REG_NUMBER)
		return (0);
	cur_proc->registers[c - 1] = cur_proc->registers[a - 1] \
	+ cur_proc->registers[b - 1];
	cur_proc->carry = (cur_proc->registers[c - 1] == 0) ? 1 : 0;
	return (1);
}
