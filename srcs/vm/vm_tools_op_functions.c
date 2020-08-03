/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_op_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 11:53:41 by yaye              #+#    #+#             */
/*   Updated: 2020/08/03 17:15:39 by mdavid           ###   ########.fr       */
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
**	<type> == 1  RETURNS value
**	<type> == 11 RETURNS cur_proc->registers[value]
*/

int		get_arg_value(t_cw *cw, t_process *cur_proc, int index, int type)
{
	int			value;
	extern t_op	op_tab[17];

	if ((type % 10) != REG_CODE || (type % 10) != IND_CODE \
		|| (type % 10) != DIR_CODE)
		return (0);
	value = cw->arena[(index) % MEM_SIZE];
	if ((type % 10) == REG_CODE)
		return (value);
	value = value << 8 | cw->arena[(index + 1) % MEM_SIZE];
	if ((type % 10) == IND_CODE)
		return ((type / 10) == 0 ? value \
			: cw->arena[(cur_proc->i + (value % IDX_MOD)) % MEM_SIZE]);
	if ((type % 10) == DIR_CODE)
	{
		if (op_tab[(int)(cur_proc->opcode)].direct_size == 1)
			return (value);
		value = value << 8 | cw->arena[(index + 2) % MEM_SIZE];
		return (value = value << 8 | cw->arena[(index + 3) % MEM_SIZE]);
	}
	return (0);
}

int		is_valid_reg(char *arena, t_process *p)
{
	if (arena && p)
		return (1);
	return (1);
}
