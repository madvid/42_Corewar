/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 10:03:54 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/20 11:47:03 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	opcode_v12(t_cw *cw, void *ptr, char *a, char **arg)
{
	extern t_op	op_tab[17];

	a = arg[0];
	ft_printf("P %4d ", ((t_process*)(ptr))->id);
	ft_printf("| %s %s (%d)\n", op_tab[((t_process*)(ptr))->opcode - 1].name \
		, args_to_str(cw, ((t_process*)(ptr))), \
		(((ft_atoi(a)) % IDX_MOD) + ((t_process*)(ptr))->i) % MEM_SIZE);
}

void	opcode_g(t_cw *cw, void *ptr, char *tmp)
{
	extern t_op	op_tab[17];

	ft_printf("P %4d ", ((t_process*)(ptr))->id);
	ft_printf("| %s %s%s\n", \
			op_tab[((t_process*)(ptr))->opcode - 1].name, \
			args_to_str(cw, ((t_process*)(ptr))), \
			(((t_process*)(ptr))->opcode == 9) ? tmp : "");
}

void	opcode_v11(void *ptr, char *a, char *b, char **arg)
{
	a = arg[1];
	b = arg[2];
	ft_printf("%7s| -> store to %s + %s = %d (with pc and mod %d)\n", "", \
		a, b, (ft_atoi(a) + ft_atoi(b)), \
		(((ft_atoi(a) + ft_atoi(b)) % IDX_MOD) + ((t_process*)(ptr))->i) \
		% MEM_SIZE);
}

void	opcode_v10(void *ptr, char *a, char *b, char **arg)
{
	a = arg[0];
	b = arg[1];
	ft_printf("%7s| -> load from %s + %s = %d (with pc and mod %d)\n", "", \
		a, b, (ft_atoi(a) + ft_atoi(b)), \
		(((ft_atoi(a) + ft_atoi(b)) % IDX_MOD) + ((t_process*)(ptr))->i) \
		% MEM_SIZE);
}

void	pcmv_print_arg(t_cw *cw, void *ptr, int i)
{
	char	*tmp;

	tmp = ft_itoa_base2((int)cw->arena[((t_process*)(ptr))->i\
			+ i] & 255, "0123456789abcdef");
	if (((int)cw->arena[((t_process*)(ptr))->i + i] & 255) < 16)
		ft_printf("0%s", tmp);
	else
		ft_printf("%s", tmp);
	ft_memdel((void**)&tmp);
	ft_printf(" ");
}
