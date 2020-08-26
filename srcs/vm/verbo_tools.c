/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 10:03:54 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/26 16:09:11 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	opcode_v12(void *ptr, t_arg a)
{
	int			tmp;
	int			tmp2;
	extern t_op	op_tab[17];

	tmp = ((t_process*)(ptr))->opcode  == 12 ? a.arg[0] % IDX_MOD \
		: a.arg[0];
	tmp2 = tmp + ((t_process*)(ptr))->i;
	tmp2 = ((t_process*)(ptr))->opcode  == 12 ? tmp2 % MEM_SIZE : tmp2;
	ft_printf("P %4d | %s %d (%d)\n", ((t_process*)(ptr))->id, \
		op_tab[((t_process*)(ptr))->opcode - 1].name, a.arg[0], tmp2);
}

void	opcode_g(void *ptr, char *tmp, t_arg a)
{
	extern t_op	op_tab[17];
	char		*all_args;

	if (!(all_args = args_to_str(a)))
		return ;
	ft_printf("P %4d | %s %s%s\n", ((t_process*)(ptr))->id, \
			op_tab[((t_process*)(ptr))->opcode - 1].name, \
			all_args, (((t_process*)(ptr))->opcode == 9) ? tmp : "");
	if (all_args)
		ft_memdel((void **)&all_args);
}

void	opcode_v11(void *ptr, t_arg a)
{
	int		tmp;
	int		ret;

	tmp =  (a.arg[0] + a.arg[1]) % IDX_MOD;
	ret =a.arg[0] + a.arg[1];
	ft_printf("%7s| -> store to %d + %d = %d (with pc and mod %d)\n", "", \
		a.arg[0], a.arg[1], ret, \
		(tmp + ((t_process*)(ptr))->i));
}

void	opcode_v10(void *ptr, t_arg a)
{
	int		tmp;
	int		ret;

	tmp = (a.arg[0] + a.arg[1]) % IDX_MOD;
	ret = a.arg[0] + a.arg[1];
	ft_printf("%7s| -> load from %d + %d = %d (with pc and mod %d)\n", "", \
		a.arg[0], a.arg[1], ret, \
		(tmp + ((t_process*)(ptr))->i));
}
