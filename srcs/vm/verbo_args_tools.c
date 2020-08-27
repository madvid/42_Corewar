/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbo_args_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 13:07:22 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/27 12:49:55 by mdavid           ###   ########.fr       */
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

static void	op_arg_type(t_op op_elem, int encod, t_arg *ag)
{
	int		i;

	if (encod == 0)
		ag->type[0] = T_DIR;
	else
	{
		i = -1;
		while (++i < 3)
		{
			if (i < (int)op_elem.n_arg)
			{
				ag->type[i] = (encod & (192 >> (2 * i))) >> (8 - 2 * i);
				ft_printf(" [(encod & (192 >> (2 * i))) = %d] ag->type[%d] = %d\n", (encod & (192 >> (2 * i))), i, ag->type[i]);
				ag->type[i] = (ag->type[i] == 3) ? 4 & op_elem.type[i] \
					: ag->type[i] & op_elem.type[i];
			}
			else
				ag->type[i] = 0;
		}
	}
}

/*
** Function: op_arg_type_shift
** Description:
**	Performs a shift type if necessary, on arg->type[i].
**	It is necessary to transforms the type if ...
*/

static void	op_arg_type_shift(int shift, t_arg *ag)
{
	if (shift == 10)
		ag->type[0] = DIR_CODE;
	if (shift == 20)
		ag->type[1] = DIR_CODE;
	if (shift == 30)
		ag->type[2] = DIR_CODE;
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
	op_arg_type(op_tab[p->opcode - 1], encod % RELATIVE, &arg);
	op_arg_type_shift(encod - (encod % RELATIVE), &arg);
	if (arg.type[0] != 0)
		arg.arg[0] = a1;
	if (arg.type[1] != 0)
		arg.arg[1] = a2;
	if (arg.type[2] != 0)
		arg.arg[2] = a3;
	if (p->opcode == 1 || p->opcode == 9 || p->opcode == 12 || p->opcode == 15)
		arg.widht = 5 - 2 * op_tab[p->opcode -1].direct_size;
	else
		arg.widht = instruction_width(encod, op_tab[p->opcode - 1]) \
			+ 1 + op_tab[p->opcode - 1].encod;
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
