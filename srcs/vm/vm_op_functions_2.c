/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:05:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/31 18:02:54 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_soustraction
** Description:
**		* Writes in cur_proc->registers[ARG_3] the result of the soustraction
**		cur_proc->registers[ARG_1] - cur_proc->registers[ARG_2]
**		* cur->carry is set to 1 (if result of soustraction is 0) else 0 (else)
** Return:
**	0: in every case
*/

int		op_soustraction(t_cw *cw, t_process *p)
{
	t_arg		v_arg;

	op_arg_init(&v_arg, REG_CODE, 7);
	v_arg.arg[0] = cw->arena[(p->i + 2) % MEM_SIZE];
	v_arg.arg[1] = cw->arena[(p->i + 3) % MEM_SIZE];
	v_arg.arg[2] = cw->arena[(p->i + 4) % MEM_SIZE];
	p->registers[v_arg.arg[2] - 1] = p->registers[v_arg.arg[0] - 1] \
		- p->registers[v_arg.arg[1] - 1];
	p->carry = (p->registers[v_arg.arg[2] - 1] == 0) ? 1 : 0;
	if (cw->options->verbose == true)
		verbotab(cw, p, v_arg);
	return (0);
}

/*
** Function: op_and
** Description:
**	Normalement ça marche <- Merci de la description Yannick !
** Return:
**	0:
*/

int		op_and(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	t_arg		v_arg;
	int			a;
	int			b;
	int			c;

	op_arg_init(&v_arg, DIR_CODE, 3);
	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw, p, p->i + 2, a + RELATIVE);
	v_arg.arg[0] = a;
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw, p, p->i + 2 + c, b + RELATIVE);
	v_arg.arg[1] = b;
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	c = get_arg_value(cw, p, p->i + 2 + c, REG_CODE);
	v_arg.arg[2] = c;
	v_arg.type[2] = REG_CODE;
	p->registers[c - 1] = a & b;
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	verbotab(cw, p, v_arg);
	return (0);
}

/*
** Function: op_or
** Description:
**	Comme op_and
** Return:
**	0:
*/

int		op_or(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	t_arg		v_arg;
	int			a;
	int			b;
	int			c;

	op_arg_init(&v_arg, DIR_CODE, 3);
	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw, p, p->i + 2, a + RELATIVE);
	v_arg.arg[0] = a;
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw, p, p->i + 2 + c, b + RELATIVE);
	v_arg.arg[1] = b;
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	c = get_arg_value(cw, p, p->i + 2 + c, REG_CODE);
	v_arg.arg[2] = c;
	v_arg.type[2] = REG_CODE;
	p->registers[c - 1] = a | b;
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	verbotab(cw, p, v_arg);
	return (0);
}

/*
** Function: op_xor
** Description:
**	Idem
** Return:
**	0:
*/

int		op_xor(t_cw *cw, t_process *p)
{
	extern t_op	op_tab[17];
	t_arg		v_arg;
	int			a;
	int			b;
	int			c;

	op_arg_init(&v_arg, DIR_CODE, 3);
	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw, p, p->i + 2, a + RELATIVE);
	v_arg.arg[0] = a;
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw, p, p->i + 2 + c, b + RELATIVE);
	v_arg.arg[1] = b;
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	c = get_arg_value(cw, p, p->i + 2 + c, REG_CODE);
	v_arg.arg[2] = c;
	v_arg.type[2] = REG_CODE;
	p->registers[c - 1] = a ^ b;
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	verbotab(cw, p, v_arg);
	return (0);
}
