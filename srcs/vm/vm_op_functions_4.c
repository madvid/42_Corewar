/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_functions_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:06:21 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/07 09:59:05 by armajchr         ###   ########.fr       */
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
	int			i;

	a = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6;
	a = get_arg_value(cw->arena, p, p->i + 2, a);
	if (((cw->arena[(p->i + 1) % MEM_SIZE] & 0b11000000) >> 6) == IND_CODE)
		a = cw->arena[(p->i + a) % MEM_SIZE];
	b = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[p->opcode - 1].direct_size);
	b = get_arg_value(cw->arena, p, p->i + 2 + b, REG_CODE);
	p->carry = (a == 0) ? 1 : 0;
	p->registers[b - 1] = a;
	return (i = (cw->options.verbose == true) ? init_verbotab(cw, p, 1) : 1);
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
		& 0b11000000, op_tab[p->opcode - 1].direct_size);
	b = (cw->arena[(p->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
	b = get_arg_value(cw->arena, p, p->i + 2 + c, b + RELATIVE);
	c = instruction_width(cw->arena[(p->i + 1) % MEM_SIZE] \
		& 0b11110000, op_tab[p->opcode - 1].direct_size);
	c = get_arg_value(cw->arena, p, p->i + 2 + c, REG_CODE);
	p->registers[c - 1] = cw->arena[(p->i + a + b) % MEM_SIZE];
	return (i = (cw->options.verbose == true) ? init_verbotab(cw, p, 1) : 1);
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
	t_list		*new_link;
	t_process	*new_proc;
	int			i;

	printf("long fork instruction en cours\n");
	addr = get_arg_value(cw->arena, cur_proc, cur_proc->i + 1, DIR_CODE);
	if (!(new_link = ft_lstnew((void*)(cur_proc), sizeof(t_process))))
		return (-1);
	new_proc = (t_process*)(new_link->cnt);
	if (!(new_proc->registers = (int*)ft_memalloc(sizeof(int) * REG_NUMBER)))
		return (-1);
	i = -1;
	while (++i < 16)
		new_proc->registers[i] = cur_proc->registers[i];
	new_proc->pc = cur_proc->i + (addr % IDX_MOD);
	new_proc->id = ((t_process*)(cw->process->cnt))->id + 1;
	new_proc->n_lives = 0;
	new_proc->wait_cycles = 0;
	new_proc->i = cur_proc->i;
	new_proc->champ = cur_proc->champ;
	ft_lstadd(&(cw->process), new_link);
	return (i = (cw->options.verbose == true) ? init_verbotab(cw, cur_proc, 1) : 1);
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
	int			i;

	printf("Aff instruction en cours\n");
	reg = get_arg_value(cw->arena, cur_proc, cur_proc->i, REG_CODE);
	arg = cur_proc->registers[reg - 1];
	if (cw->options.aff == true)
		ft_printf("Aff: %s\n", ft_itoa(arg)); // Pas le bon affichage, faire des tests pour savoir
	return (i = (cw->options.verbose == true) ? init_verbotab(cw, cur_proc,1) : 1);;
}
