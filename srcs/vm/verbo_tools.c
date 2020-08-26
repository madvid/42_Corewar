/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 10:03:54 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/26 14:27:16 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	opcode_v12(t_cw *cw, void *ptr, t_arg *a)
{
	int			tmp;
	int			tmp2;
	extern t_op	op_tab[17];

	a = arg[0];
	tmp = ((t_process*)(ptr))->opcode  == 12 ? a->arg[0] % IDX_MOD \
		: a->arg[0];
	tmp2 = tmp + ((t_process*)(ptr))->i;
	tmp2 = ((t_process*)(ptr))->opcode  == 12 ? tmp2 % MEM_SIZE : tmp2;
	ft_printf("P %4d | %s %d (%d)\n", ((t_process*)(ptr))->id, \
		op_tab[((t_process*)(ptr))->opcode - 1].name, arg[0], tmp2);
}

void	opcode_g(t_cw *cw, void *ptr, char *tmp, t_arg *a)
{
	extern t_op	op_tab[17];
	char		*all_args;

	if (!(all_args = args_to_str(a)))
		return ;
	ft_printf("P %4d | %s %s%s\n", ((t_process*)(ptr))->id),\
			op_tab[((t_process*)(ptr))->opcode - 1].name, \
			all_args, (((t_process*)(ptr))->opcode == 9) ? tmp : "");
	if (all_args)
		ft_memdel((void **)&all_args);
}

void	opcode_v11(void *ptr, t_arg *a)
{
	int		tmp;

	tmp =  (a->arg[0] + arg[1]) % IDX_MOD;
	ft_printf("%7s| -> store to %s + %s = %d (with pc and mod %d)\n", "", \
		a->arg[0], a->arg[1], (a->arg[0] + a->arg[1], \
		(tmp + ((t_process*)(ptr))->i));
}

void	opcode_v10(void *ptr, t_arg *a)
{
	int		tmp;

	a = arg[0];
	b = arg[1];
	tmp = (a->arg[0] + a->arg[1]) % IDX_MOD;
	ft_printf("%7s| -> load from %s + %s = %d (with pc and mod %d)\n", "", \
		a->arg[0], a->arg[1], (a->arg[0] + a->arg[1], \
		(tmp + ((t_process*)(ptr))->i));
}
