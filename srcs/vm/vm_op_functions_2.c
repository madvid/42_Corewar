/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:05:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/19 10:55:01 by mdavid           ###   ########.fr       */
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
**	[value_1]: 1 if encoding byte and arguments are valid
**	[value_2]: 0 else
*/

int		op_soustraction(t_cw *cw, t_process *cur_proc)
{
	int		a;
	int		b;
	int		c;
	int		i;

	a = cw->arena[(cur_proc->i + 2) % MEM_SIZE];
	b = cw->arena[(cur_proc->i + 3) % MEM_SIZE];
	c = cw->arena[(cur_proc->i + 4) % MEM_SIZE];
	if (a < 1 || a > REG_NUMBER || b < 1 || b > REG_NUMBER \
		|| c < 1 || c > REG_NUMBER)
		return (i = (cw->options->verbose == true) ? init_verbotab(cw, cur_proc, 0) : 0);
	cur_proc->registers[c - 1] = cur_proc->registers[a - 1] \
	- cur_proc->registers[b - 1];
	cur_proc->carry = (cur_proc->registers[c - 1] == 0) ? 1 : 0;
	return (i = (cw->options->verbose == true) ? init_verbotab(cw, cur_proc, 1) : 1);
}

/*
** Function: op_and
** Description:
**	Normalement ça marche
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_and(t_cw *cw, t_process *p)
{
	int			a;
	int			b;
	int			c;
	extern t_op	op_tab[17];
	int			i;

	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw->arena, p, p->i + 2, a + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1].direct_size);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1].direct_size);
	c = get_arg_value(cw->arena, p, p->i + 2 + c, REG_CODE);
	p->registers[c - 1] = a & b;
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	return (i = (cw->options->verbose == true) ? init_verbotab(cw, p, 1) : 1);
}

/*
** Function: op_or
** Description:
**	Comme op_and
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_or(t_cw *cw, t_process *p)
{
	extern t_op op_tab[17];
	int		a;
	int		b;
	int		c;
	int		i;

	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw->arena, p, p->i + 2, a + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1].direct_size);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1].direct_size);
	c = get_arg_value(cw->arena, p, p->i + 2 + c, REG_CODE);
	p->registers[c - 1] = a | b;
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	return (i = (cw->options->verbose == true) ? init_verbotab(cw, p, 1) : 1);
}

/*
** Function: op_xor
** Description:
**	Idem
** Return:
**	[value_1]:
**	[value_2]:
*/

int		op_xor(t_cw *cw, t_process *p)
{
	extern t_op op_tab[17];
	int		a;
	int		b;
	int		c;

	(cw->options->verbose == true) ? init_verbotab(cw, p, 1) : 1;
	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	// cw->tot_cycle >= 6030 ? ft_printf("    [xor]: type de <ARG1> = %d\n", a) : 0;
	a = get_arg_value(cw->arena, p, p->i + 2, a + RELATIVE);
	// cw->tot_cycle >= 6030 ? ft_printf("    [xor]: val de <ARG1> = %d\n", a) : 0;
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1].direct_size);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	// cw->tot_cycle >= 6030 ? ft_printf("    [xor]: type de <ARG2> = %d\n", b) : 0;
	b = get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE);
	// cw->tot_cycle >= 6030 ? ft_printf("    [xor]: val de <ARG2> = %d\n", b) : 0;
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1].direct_size);
	// cw->tot_cycle >= 6030 ? ft_printf("    [xor]: largeur de <ARG1> + <ARG2> = %d\n", c) : 0;
	c = get_arg_value(cw->arena, p, p->i + 2 + c, REG_CODE);
	// cw->tot_cycle >= 6030 ? ft_printf("    [xor]: val de <ARG3>(reg attendu) = %d\n", c) : 0;
	p->registers[c - 1] = a ^ b;
	p->carry = (p->registers[c - 1] == 0) ? 1 : 0;
	return (1);
}

