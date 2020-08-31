/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:06:21 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/31 18:27:59 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_long_load
** Description:
**	[put some explanations here !]
** Return:
**	0:
*/

int		op_long_load(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	t_arg		v_arg;
	int			a;
	int			b;

	op_arg_init(&v_arg, DIR_CODE, 1);
	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw->arena, p, p->i + 2, a + RELATIVE);
	v_arg.arg[0] = a;
	b = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	b = get_arg_value(cw->arena, p, p->i + 2 + b, REG_CODE);
	v_arg.arg[1] = b;
	v_arg.type[1] = REG_CODE;
	p->carry = (a == 0) ? 1 : 0;
	p->registers[b - 1] = a;
	verbotab(cw, p, v_arg);
	return (0);
}

/*
** Function: op_long_load_index
** Description:
**	[put some explanations here !]
** Return:
**	0:
*/

int		op_long_load_index(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	t_arg		v_arg;
	int			arg[3];

	op_arg_init(&v_arg, DIR_CODE, 3);
	arg[0] = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	arg[0] = get_arg_value(cw->arena, p, p->i + 2, arg[0] + RELATIVE);
	v_arg.arg[0] = arg[0];
	arg[2] = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	arg[1] = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	v_arg.arg[1] = get_arg_value(cw->arena, p, p->i + 2 + arg[2], \
		arg[1] + RELATIVE);
	arg[1] = arg[0] + v_arg.arg[1] + p->i;
	arg[1] = (arg[1] < 0) ? MEM_SIZE + (arg[1] % MEM_SIZE) : arg[1] % MEM_SIZE;
	arg[2] = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	arg[2] = get_arg_value(cw->arena, p, p->i + 2 + arg[2], REG_CODE);
	v_arg.arg[2] = arg[2];
	v_arg.type[2] = REG_CODE;
	p->registers[arg[2] - 1] = (cw->arena[arg[1]] << 24) & 0xFF000000;
	write_in_reg(cw, p, arg);
	verbotab(cw, p, v_arg);
	return (0);
}

/*
** Function: op_long_fork
** Description:
**	[put some explanations here !]
** Return:
**	0: the process is correctly created
**	CD_FORK: a memory allocation issue occurs during the lfork instruction
*/

int		op_long_fork(t_cw *cw, t_process *p)
{
	t_arg		v_arg;
	int			addr;

	op_arg_init(&v_arg, DIR_CODE, 1);
	addr = get_arg_value(cw->arena, p, p->i + 1, DIR_CODE);
	v_arg.arg[0] = addr;
	if (!fork_creation_process(cw, p, addr))
		return (CD_FORK);
	verbotab(cw, p, v_arg);
	return (0);
}

/*
** Function: op_aff
** Description:
**	Aff simply shows the content of the specified register.
** Return:
**	0: if no memory allocation occurs.
**	-1: if allocation of the string failed
** Remarks:
**	We chosen to not raise an error (a specific cd_error) due to the role
**	of Aff: it does not modify the arena or the content of a register. Thus
**	it success or fail does not affect the run of the game.
*/

int		op_aff(t_cw *cw, t_process *p)
{
	t_arg		v_arg;
	int			arg;
	char		*str;
	u_int8_t	reg;

	op_arg_init(&v_arg, 0, 0);
	v_arg.widht = 3;
	reg = get_arg_value(cw->arena, p, p->i, REG_CODE);
	arg = p->registers[reg - 1];
	if (cw->options->aff == true)
	{
		if (!(str = ft_itoa(arg)))
			return (-1);
		ft_printf("Aff: %s\n", str);
		ft_strdel(&str);
	}
	if (cw->options->v_lvl & 0b00010000)
		vprint_pcmv(cw, p, v_arg);
	return (0);
}
