/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:04:59 by mdavid            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/07/30 12:31:25 by mdavid           ###   ########.fr       */
=======
/*   Updated: 2020/07/30 11:12:58 by armajchr         ###   ########.fr       */
>>>>>>> e9bdf4cfda4c623beeb5b7c5e067b403eb9f0b69
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

int		op_alive(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		arg;

	index = cur_proc->position - (void*)(cw->arena);
	printf("Alive en cours.\n");
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	arg = (cw->arena[(index + 1) % MEM_SIZE] & 255) << 24
		| (cw->arena[(index + 2) % MEM_SIZE] & 255) << 16
		| (cw->arena[(index + 3) % MEM_SIZE] & 255) << 8
		| (cw->arena[(index + 4) % MEM_SIZE] & 255);
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

int		op_load(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int			index;
	int			arg;
	u_int8_t	reg;

	printf("Load instruction en cours\n");
	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	if ((((cw->arena[(index + 1) % MEM_SIZE]) & 0b11000000) >> 6) == DIR_CODE)
	{
		reg = (cw->arena[(index + 6) % MEM_SIZE] & 255);
		if (!(reg >= 0 && reg < 16))
			return (0);
		arg = (cw->arena[(index + 2) % MEM_SIZE] & 255) << 24
		| (cw->arena[(index + 3) % MEM_SIZE] & 255) << 16
		| (cw->arena[(index + 4) % MEM_SIZE] & 255) << 8
		| (cw->arena[(index + 5) % MEM_SIZE] & 255);
		cur_proc->carry = (arg == 0) ? 1 : 0;
		cur_proc->registers[reg - 1] = arg; // changer registers en tableau de int.
		// printf("     cur_proc->registers[%d - 1] = %d\n", reg, arg);
	}
	if ((((cw->arena[(index + 1) % MEM_SIZE]) & 0b11000000) >> 6) == IND_CODE)
	{
		reg = (cw->arena[(index + 4) % MEM_SIZE] & 255);
		if (!(reg >= 0 && reg < 16))
			return (0);
	}
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

int		op_store(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int			index;
	int			a;
	int			b;

	printf("Store instruction en cours\n");
	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	a = cw->arena[(index + 2) % MEM_SIZE];
	if (a < 1 || a > REG_NUMBER)
		return (0);
	b = cw->arena[(index + 3) % MEM_SIZE];
	if (((cw->arena[(index + 1) % MEM_SIZE] & 0b00110000) >> 4) == IND_CODE)
	{
		b = (b << 8) | cw->arena[(index + 4) % MEM_SIZE];
		printf("     (index + (b %% IDX_MOD)) %% MEM_SIZE = %d\n", (index + (b % IDX_MOD)) % MEM_SIZE);
		printf("     (index + ((b+1) %% IDX_MOD)) %% MEM_SIZE = %d\n", (index + ((b+1) % IDX_MOD)) % MEM_SIZE);
		printf("     (index + ((b+2) %% IDX_MOD)) %% MEM_SIZE = %d\n", (index + ((b+2) % IDX_MOD)) % MEM_SIZE);
		printf("     (index + ((b+3) %% IDX_MOD)) %% MEM_SIZE = %d\n", (index + ((b+3) % IDX_MOD)) % MEM_SIZE);
		printf("     (cur_proc->registers[a - 1] & 4278190080) >> 24 = %lX\n", (cur_proc->registers[a - 1] & 4278190080) >> 24);
		printf("     (cur_proc->registers[a - 1] & 16711680) >> 16 = %X\n", (cur_proc->registers[a - 1] & 16711680) >> 16);
		printf("     (cur_proc->registers[a - 1] & 65280) >> 8 = %X\n", (cur_proc->registers[a - 1] & 65280) >> 8);
		printf("     (cur_proc->registers[a - 1] & 255) = %X\n", (cur_proc->registers[a - 1] & 255));
		cw->arena[(index + (b % IDX_MOD)) % MEM_SIZE] = (cur_proc->registers[a - 1] & 4278190080) >> 24;
		cw->arena[(index + ((b + 1) % IDX_MOD)) % MEM_SIZE] = (cur_proc->registers[a - 1] & 16711680) >> 16;
		cw->arena[(index + ((b + 2) % IDX_MOD)) % MEM_SIZE] = (cur_proc->registers[a - 1] & 65280) >> 8;
		cw->arena[(index + ((b + 3) % IDX_MOD)) % MEM_SIZE] = (cur_proc->registers[a - 1] & 255);
	}
	else if (((cw->arena[(index + 1) % MEM_SIZE] & 0b00110000) >> 4) == REG_CODE \
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

int		op_addition(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int		index;
	int		a;
	int		b;
	int		c;

	index = cur_proc->position - (void*)(cw->arena);
	if (op_elem.encod == 1)
		if (!is_valid_encoding(cw->arena[index], cw->arena[(index + 1) % MEM_SIZE]))
			return (0);
	a = cw->arena[(index + 2) % MEM_SIZE];
	b = cw->arena[(index + 3) % MEM_SIZE];
	c = cw->arena[(index + 4) % MEM_SIZE];
	if (a < 1 || a > REG_NUMBER || b < 1 || b > REG_NUMBER \
		|| c < 1 || c > REG_NUMBER)
		return (0);
	cur_proc->registers[c - 1] = cur_proc->registers[a - 1] + cur_proc->registers[b - 1];
	cur_proc->carry = (cur_proc->registers[c - 1] == 0) ? 1 : 0;
	return (1);
}
