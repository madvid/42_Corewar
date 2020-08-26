/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_op_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 11:53:41 by yaye              #+#    #+#             */
/*   Updated: 2020/08/25 20:48:34 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: get_arg_value
** Description:
**	RETURNS THE (RELATIVE/ABSOLUTE) VALUE OF THE ARGUMENT cw->arena[<index>]
**	<index> IS THE CORRECT INDEX OF THE VALUE IN THE ARENA
**	ARGUMENT TYPE IS <type>
**		REG_CODE 1
**		IND_CODE 3
**		DIR_CODE 2
**	<type> / 10 == 0 => RETURNS ABSOLUTE VALUE
**	<type> / 10 != 0 => RETURNS RELATIVE VALUE
** Example:
**	<type> == REG_CODE				RETURNS arg_value
**										<=>	numero du registre
**	<type> == REG_CODE + RELATIVE	RETURNS cur_proc->registers[arg_value]
**										<=> valeur du registre[arg_value]
*/

int		get_arg_value(char *arena, t_process *cur_proc, int index, int type)
{
	int			value;
	int			ret;
	extern t_op	op_tab[17];

	if ((type % 10) != REG_CODE && (type % 10) != IND_CODE \
		&& (type % 10) != DIR_CODE)
		return (0);
	value = arena[(index) % MEM_SIZE];
	if ((type % 10) == REG_CODE)
		return ((type / 10) == 0 ? value : cur_proc->registers[value - 1]);
	value = value << 8 | (unsigned char)arena[(index + 1) % MEM_SIZE];
	if ((type % 10) == IND_CODE)
	{
		if (type / 10 != 0)
		{
			value = cur_proc->i + (value % IDX_MOD);
			value = (value < 0) ? MEM_SIZE + value : value;
			ret = arena[value % MEM_SIZE] << 24
				| ((unsigned int)arena[(value + 1) % MEM_SIZE] & 255) << 16
				| ((unsigned int)arena[(value + 2) % MEM_SIZE] & 255) << 8
				| ((unsigned int)arena[(value + 3) % MEM_SIZE] & 255);
		}
		return ((type / 10) == 0 ? value : ret);
	}
	if ((type % 10) == DIR_CODE)
	{
		if (op_tab[(int)(cur_proc->opcode - 1)].direct_size == 1)
			return (value);
		value = value << 8 | (unsigned char)arena[(index + 2) % MEM_SIZE];
		return (value = value << 8 | (unsigned char)arena[(index + 3) % MEM_SIZE]);
	}
	return (0);
}

/*
** Function: is_valid_reg
** Description:
**	CHECK IF THE REGISTER VALUES ∈ [1; REG_NUMBER].
**
**	HOW <n> AND <mask> WORK:
**	n = 0		mask = 2^(7 - 2 * n) + 2^(6 - 2 * n) = 0b11000000
**	n = 1		mask = 2^(7 - 2 * n) + 2^(6 - 2 * n) = 0b00110000
**	n = 2		mask = 2^(7 - 2 * n) + 2^(6 - 2 * n) = 0b00001100
*/

bool		is_valid_reg(char *arena, t_process *p)
{
	extern t_op	op_tab[17];
	size_t		n;
	int			mask;
	int			arg;
	int			j;

	n = 0;
	j = 0;
	while (n < op_tab[p->opcode - 1].n_arg)
	{
		mask = ft_power(2, 7 - (2 * n)) + ft_power(2, 6 - (2 * n));
		arg = get_arg_value(arena, p, p->i + 2 + j, (arena[(p->i + 1) % MEM_SIZE] & mask) \
			>> (6 - (2 * n)));
		j = j + instruction_width(arena[(p->i + 1) % MEM_SIZE] \
			& mask, op_tab[p->opcode - 1]);
		if (((arena[(p->i + 1) % MEM_SIZE] & mask) >> (6 - (2 * n))) == REG_CODE)
		{
			if (arg < 1 || arg > REG_NUMBER)
				return (false);
		}
		n += 1;
	}
	return (true);
}
