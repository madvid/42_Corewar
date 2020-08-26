/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:05:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/27 00:47:09 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_soustraction
** Description:
**	- Writes in cur_proc->registers[ARG_3] the value
**    cur_proc->registers[ARG_1] - cur_proc->registers[ARG_2]
**  - cur->carry = 1 (if value == 0)
**                 0 (else)
** Return:
**	0: if encoding byte and arguments are valid
**	-1: 
*/

int		op_soustraction(t_cw *cw, t_process *p)
{
	int		a;
	int		b;
	int		c;

	a = cw->arena[(p->i + 2) % MEM_SIZE];
	b = cw->arena[(p->i + 3) % MEM_SIZE];
	c = cw->arena[(p->i + 4) % MEM_SIZE];
	if (a < 1 || a > REG_NUMBER || b < 1 || b > REG_NUMBER \
		|| c < 1 || c > REG_NUMBER)
		{
			verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, c));
			return (-1);
		}
	p->registers[c - 1] = p->registers[a - 1] \
	- p->registers[b - 1];
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, c));
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
	int			a;
	int			b;
	int			c;

	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw->arena, p, p->i + 2, a + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	c = get_arg_value(cw->arena, p, p->i + 2 + c, REG_CODE);
	p->registers[c - 1] = a & b;
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, c));
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
	int			a;
	int			b;
	int			c;

	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw->arena, p, p->i + 2, a + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	c = get_arg_value(cw->arena, p, p->i + 2 + c, REG_CODE);
	p->registers[c - 1] = a | b;
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, c));
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
	int			a;
	int			b;
	int			c;

	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw->arena, p, p->i + 2, a + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1]);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1]);
	c = get_arg_value(cw->arena, p, p->i + 2 + c, REG_CODE);
	verbotab(cw, p, op_arg(cw->arena[(p->i + 1) % MEM_SIZE], p, a, b, c));
	p->registers[c - 1] = a ^ b;
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	return (0);
}
