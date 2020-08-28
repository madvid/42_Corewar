/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbo_args_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 13:07:22 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/26 17:11:48 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: op_arg_init
** Description:
**	Initialize table type and arg to 0 and width to -1;
*/

static void	op_arg_init(t_arg *arg)
{
	arg->type[0] = 0;
	arg->type[1] = 0;
	arg->type[2] = 0;
	arg->arg[0] = 0;
	arg->arg[1] = 0;
	arg->arg[2] = 0;
	arg->widht = -1;
}

/*
** Function: op_arg_type
** Description:
**	Records of the type of the arguments.
**	If there is no encod, it means there is only one arg of direct type.
**	If there is an encoded byte, type from this one are extracted and compare
**	with what type is expected based on the opcode.
*/

static void	op_arg_type(t_op op_tab[17], int encod, t_process *p, t_arg *ag)
{
	int		i;

	if (encod == 0)
	{
		ag->type[0] = T_DIR;
		ag->type[1] = 0;
		ag->type[2] = 0;
	}
	else
	{
		i = -1;
		while (++i < 3)
		{
			ag->type[i] = ((int)op_tab[p->opcode -1].n_arg >= i + 1) ? \
				((encod & 192) >> (2 * i)) >> (8 - 2 * (i + 1)) : 0;
			if ((int)op_tab[p->opcode -1].n_arg >= i + 1)
				ag->type[i] = (ag->type[i] == 3) ? \
				4 & op_tab[p->opcode -1].type[0] \
				: ag->type[i] & op_tab[p->opcode -1].type[i];
		}
	}
}

/*
** Function: op_arg
** Description:
**	
** Return:
**	
*/

t_arg		op_arg(int encod, t_process *p, int a1, int a2, int a3)
{
	extern t_op	op_tab[17];
	t_arg	arg;
	
	op_arg_init(&arg);
	op_arg_type(op_tab, encod, p, &arg);
	if (arg.type[0] != 0)
		arg.arg[0] = a1;
	if (arg.type[1] != 0)
		arg.arg[1] = a2;
	if (arg.type[2] != 0)
		arg.arg[2] = a3;
	if (p->opcode == 1 || p->opcode == 9 || p->opcode == 12 || p->opcode == 15)
		arg.widht = 5 - 2 * op_tab[p->opcode -1].direct_size;
	else
		arg.widht = instruction_width(encod, op_tab[p->opcode - 1]) + 1 + op_tab[p->opcode - 1].encod;
	return (arg);
}

void		tool_print_t_arg(t_arg arg)
{
	ft_printf(">> T_ARG <<");
	ft_printf(" - arg.type[0] = %d", arg.type[0]);
	ft_printf(" - arg.type[1] = %d", arg.type[1]);
	ft_printf(" - arg.type[2] = %d", arg.type[2]);
	ft_printf(" - arg.arg[0] = %d", arg.arg[0]);
	ft_printf(" - arg.arg[1] = %d", arg.arg[1]);
	ft_printf(" - arg.arg[2] = %d", arg.arg[2]);
	ft_printf(" - arg.widht = %d\n", arg.widht);
}
