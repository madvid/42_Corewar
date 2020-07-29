/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_op_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 11:53:41 by yaye              #+#    #+#             */
/*   Updated: 2020/07/29 11:53:42 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: get_arg_value
** Description:
**	USED FOR OPERATION WHICH DIRECT_SIZE == 0
**	RETURNS THE (RELATIVE/ABSOLUTE) VALUE OF THE ARGUMENT cw->arena[<index>]
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
	int		i0;
	int		value;

	i0 = cur_proc->position - (void *)(cw->arena);
	value = cw->arena[(index) % MEM_SIZE];
	if ((type % 10) == REG_CODE)
		return ((type / 10) ? value : cur_proc->registers[value]);
	value = value << 8 | cw->arena[(index + 1) % MEM_SIZE];
	if ((type % 10) == IND_CODE)
		return ((type / 10) ? value : cw->arena[(i0 + (value % IDX_MOD)) % MEM_SIZE]);
	value = value << 8 | cw->arena[(index + 2) % MEM_SIZE];
	if ((type % 10) == DIR_CODE)
		return (value = value << 8 | cw->arena[(index + 3) % MEM_SIZE]);
	return (0);
}
