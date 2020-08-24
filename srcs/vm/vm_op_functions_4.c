/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:06:21 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/24 23:51:50 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_long_load
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_long_load(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	int			a;
	int			b;

	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw->arena, p, p->i + 2, a + RELATIVE);
	b = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	b = get_arg_value(cw->arena, p, p->i + 2 + b, REG_CODE);
	p->carry = (a == 0) ? 1 : 0;
	p->registers[b - 1] = a;
	return ((cw->options->verbose == true) ? init_verbotab(cw, p, 1) : 1);
}

/*
** Function: op_long_load_index
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_long_load_index(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	int			a;
	int			b;
	int			c;
	int			i;

	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw->arena, p, p->i + 2, a + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = a + get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE) + p->i;
	b = (b < 0) ? MEM_SIZE + (b % MEM_SIZE) : b % MEM_SIZE;
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	c = get_arg_value(cw->arena, p, p->i + 2 + c, REG_CODE);
	p->registers[c - 1] = (cw->arena[b] << 24) & 0xFF000000;
	i = 0;
	while (++i < 4)
		p->registers[c - 1] += (((unsigned char)(cw->arena[(b + i) \
			% MEM_SIZE])) << (24 - 8 * i)) & (0xFF000000 >> (8 * i));
	return ((cw->options->verbose == true) ? init_verbotab(cw, p, 1) : 1);
}

/*
** Function: op_long_fork
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_long_fork(t_cw *cw, t_process *cur_proc)
{
	int			addr;

	addr = get_arg_value(cw->arena, cur_proc, cur_proc->i + 1, DIR_CODE);
	if (!fork_creation_process(cw, cur_proc, addr))
		return (vm_error_manager(CD_FORK, NULL, &cw));
	return (cw->options->verbose ? init_verbotab(cw, cur_proc, 1) : 1);
}

/*
** Function: op_aff
** Description:
**	[put some explanations here !]
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_aff(t_cw *cw, t_process *cur_proc)
{
	int			arg;
	u_int8_t	reg;

	reg = get_arg_value(cw->arena, cur_proc, cur_proc->i, REG_CODE);
	arg = cur_proc->registers[reg - 1];
	if (cw->options->aff == true)
		ft_printf("Aff: %s\n", ft_itoa(arg));
	return (cw->options->verbose ? init_verbotab(cw, cur_proc, 1) : 1);
}
