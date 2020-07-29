/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:04:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/29 16:13:37 by mdavid           ###   ########.fr       */
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
	if (((u_int8_t)(cw->arena[(index + 1) % MEM_SIZE]) & 0b11000000) == 2)
	{
		reg = (cw->arena[(index + 6) % MEM_SIZE] & 255);
		if (!(reg >= 0 && reg < 16))
			return (0);
		arg = (cw->arena[(index + 1) % MEM_SIZE] & 255) << 24
		| (cw->arena[(index + 2) % MEM_SIZE] & 255) << 16
		| (cw->arena[(index + 3) % MEM_SIZE] & 255) << 8
		| (cw->arena[(index + 4) % MEM_SIZE] & 255);
		cur_proc->carry = (arg == 0) ? 1 : 0;
		cur_proc->registers[reg] = arg; // changer registers en tableau de int.
		return (1);
	}
	if (((u_int8_t)(cw->arena[(index + 1) % MEM_SIZE]) & 0b11000000) == 3)
	{
		reg = (cw->arena[(index + 6) % MEM_SIZE] & 255);
		if (!(reg >= 0 && reg < 16))
			return (0);
		return (1);
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

int		op_store(t_cw *cw, t_process *cur_proc, t_op op_elem)
{
	int			index;
	u_int8_t	encoding;
	u_int8_t	a;
	u_int8_t	b;

	index = cur_proc->position - (void*)(cw->arena);
	encoding = cw->arena[(index + 1) % MEM_SIZE];
	printf("Store instruction en cours\n");
	if (!is_valid_encoding(op_elem.code, encoding))
		return (0);
	a = cw->arena[(index + 2) % MEM_SIZE];
	if (a < 0 || a >= REG_NUMBER)
		return (0);
	b = cw->arena[(index + 3) % MEM_SIZE];
	if (((encoding & 0b00110000) >> 4) == IND_CODE)
	{
		b = b << 8 | (cw->arena[(index + 4) % MEM_SIZE]);
		cw->arena[(index + (b % IDX_MOD)) % MEM_SIZE] = cur_proc->registers[a];
		return (1);
	}
	else if (((encoding & 0b00110000) >> 4) == REG_CODE && b >= 0 && b < REG_NUMBER)
	{
		cur_proc->registers[b] = cur_proc->registers[a];
		return (1);
	}
	else
		return (0);
}

/*
** Function: op_adition
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
	a = (cw->arena[(index + 2) % MEM_SIZE] & 255);
	b = (cw->arena[(index + 3) % MEM_SIZE] & 255);
	c = (cw->arena[(index + 4) % MEM_SIZE] & 255);
	if (a < 0 || a > 99 || b < 0 || b > 99 || c < 0 || c > 99)	//valeurs limites à revoir
		return (0);
	cur_proc->registers[c] = cur_proc->registers[a] + cur_proc->registers[b];
	cur_proc->carry = (cur_proc->registers[c] == 0) ? 1 : 0;
	return (1);
}
