/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_op_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 11:53:41 by yaye              #+#    #+#             */
/*   Updated: 2020/08/31 20:01:37 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	write_in_reg(t_cw *cw, t_process *p, int arg[3])
{
	int		i;

	i = 0;
	while (++i < 4)
		p->registers[arg[2] - 1] += (((unsigned char)(cw->arena[(arg[1] + i) \
			% MEM_SIZE])) << (24 - 8 * i)) & (0xFF000000 >> (8 * i));
}

void	write_in_arena(t_cw *cw, t_process *p, int arg[3])
{
	int			i;

	cw->arena[arg[2] % MEM_SIZE] = (arg[0] & 0xFF000000) >> 24;
	cw->id_arena[arg[2] % MEM_SIZE] = p->champ->id;
	i = 0;
	while (++i < 4)
	{
		cw->arena[(arg[2] + i) % MEM_SIZE] = (unsigned char)((arg[0] \
			& (0xFF000000 >> (8 * i))) >> (24 - (8 * i)));
		cw->id_arena[(arg[2] + i) % MEM_SIZE] = p->champ->id;
	}
}

/*
** Function: op_arg_init
** Description:
**	Initialize table type and arg to 0 and width to -1;
*/

void	op_arg_init(t_arg *arg, int type0, int type_select)
{
	arg->type[0] = (type_select & 0b00000001) ? type0 : 0;
	arg->type[1] = (type_select & 0b00000010) ? type0 : 0;
	arg->type[2] = (type_select & 0b00000100) ? type0 : 0;
	arg->arg[0] = 0;
	arg->arg[1] = 0;
	arg->arg[2] = 0;
	arg->widht = -1;
}

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

int		get_arg_value(t_cw *cw, t_process *cur_proc, int i, int t)
{
	int			arg;
	int			relative_ind;

	if ((t % 10) != REG_CODE && (t % 10) != IND_CODE && (t % 10) != DIR_CODE)
		return (0);
	arg = cw->arena[i % MEM_SIZE];
	if ((t % 10) == REG_CODE)
		return ((t / 10) == 0 ? arg : cur_proc->registers[arg - 1]);
	arg = arg << 8 | (unsigned char)cw->arena[(i + 1) % MEM_SIZE];
	if ((t % 10) == IND_CODE)
	{
		if (t / 10 == 1)
		{
			arg = cur_proc->i + (arg % IDX_MOD);
			arg = (arg < 0) ? MEM_SIZE + arg : arg;
			relative_ind = cw->arena[arg % MEM_SIZE] << 24
				| ((unsigned int)cw->arena[(arg + 1) % MEM_SIZE] & 255) << 16
				| ((unsigned int)cw->arena[(arg + 2) % MEM_SIZE] & 255) << 8
				| ((unsigned int)cw->arena[(arg + 3) % MEM_SIZE] & 255);
		}
		return ((t / 10) == 0 ? arg : relative_ind);
	}
	if ((t % 10) == DIR_CODE)
	{
		if (cw->op_tab[(int)(cur_proc->opcode - 1)].direct_size == 1)
			return (arg);
		arg = arg << 8 | (unsigned char)cw->arena[(i + 2) % MEM_SIZE];
		return (arg = arg << 8 | (unsigned char)cw->arena[(i + 3) % MEM_SIZE]);
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

bool	is_valid_reg(t_cw *cw, t_process *p)
{
	size_t		n;
	int			mask;
	int			arg;
	int			j;

	n = 0;
	j = 0;
	while (n < cw->op_tab[p->opcode - 1].n_arg)
	{
		mask = ft_power(2, 7 - (2 * n)) + ft_power(2, 6 - (2 * n));
		arg = get_arg_value(cw, p, p->i + 2 + j, \
			(cw->arena[(p->i + 1) % MEM_SIZE] & mask) >> (6 - (2 * n)));
		j = j + instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
			& mask, cw->op_tab[p->opcode - 1]);
		if (((cw->arena[(p->i + 1) % MEM_SIZE] & mask) >> (6 - (2 * n))) \
			== REG_CODE)
		{
			if (arg < 1 || arg > REG_NUMBER)
				return (false);
		}
		n += 1;
	}
	return (true);
}
