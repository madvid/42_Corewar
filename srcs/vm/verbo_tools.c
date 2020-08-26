/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 10:03:54 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/26 09:31:39 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	opcode_v12(t_cw *cw, void *ptr, char *a, char **arg)
{
	int			tmp;
	int			tmp2;
	extern t_op	op_tab[17];

	a = arg[0];
	tmp = ((t_process*)(ptr))->opcode  == 12 ? ft_atoi(a) % IDX_MOD : ft_atoi(a);
	tmp2 = tmp + ((t_process*)(ptr))->i;
	tmp2 = ((t_process*)(ptr))->opcode  == 12 ? tmp2 % MEM_SIZE : tmp2;
	ft_printf("P %4d ", ((t_process*)(ptr))->id);
	ft_printf("| %s %s (%d)\n", op_tab[((t_process*)(ptr))->opcode - 1].name \
		, args_to_str(cw, ((t_process*)(ptr))), \
		tmp2);
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
	int		tmp;

	a = arg[1];
	b = arg[2];
	tmp = (ft_atoi(a) + ft_atoi(b)) % IDX_MOD;
	ft_printf("%7s| -> store to %s + %s = %d (with pc and mod %d)\n", "", \
		a, b, (ft_atoi(a) + ft_atoi(b)), \
		(tmp + ((t_process*)(ptr))->i));
}

void	opcode_v10(void *ptr, char *a, char *b, char **arg)
{
	int		tmp;

	a = arg[0];
	b = arg[1];
	tmp = (ft_atoi(a) + ft_atoi(b)) % IDX_MOD;
	ft_printf("%7s| -> load from %s + %s = %d (with pc and mod %d)\n", "", \
		a, b, (ft_atoi(a) + ft_atoi(b)), \
		(tmp + ((t_process*)(ptr))->i));
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
