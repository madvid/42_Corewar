/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbo_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 15:08:02 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/26 11:40:27 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char		*arg3_str(t_cw *cw, t_process *proc, char *dst, u_int8_t encoding)
{
	int			arg;
	int			widht;
	extern t_op	op_tab[17];

	if (op_tab[proc->opcode - 1].n_arg >= 3)
	{
		widht = instruction_width(cw->arena[(proc->i + 1) % MEM_SIZE] \
			& 0b11110000, op_tab[proc->opcode - 1]);
		arg = (cw->arena[(proc->i + 1) % MEM_SIZE] & 0b00001100) >> 2;
		arg = get_arg_value(cw->arena, proc, proc->i + 2 + widht, \
		(arg == IND_CODE) ? arg + RELATIVE : arg);
		if (proc->opcode == 11)
		{
			dst = ft_strjoin(dst, (((encoding & 0b00001100) >> 2) == REG_CODE \
				? ft_itoa(get_arg_value(cw->arena, proc, proc->i + 2 + widht, \
				(REG_CODE + RELATIVE))) : ft_itoa(arg)));
		}
		else
		{
			dst = ft_strjoin(dst, (((encoding & 0b00001100) >> 2) == REG_CODE \
				? ft_strjoin("r", ft_itoa(arg)) : ft_itoa(arg)));
		}
	}
	return (dst);
}

char		*arg2_into_str(t_cw *cw, t_process *proc, char *dst, int arg)
{
	u_int8_t	encoding;
	int			widht;
	extern t_op	op_tab[17];

	encoding = cw->arena[(proc->i + 1) % MEM_SIZE];
	widht = instruction_width(cw->arena[(proc->i + 1) % MEM_SIZE] \
		& 0b11000000, op_tab[proc->opcode - 1]);
	if (proc->opcode == 11 || proc->opcode == 10 || proc->opcode == 8)
	{
		dst = ft_strjoin_1sp(dst, (((encoding & 0b00110000) >> 4) == REG_CODE \
			? ft_itoa(get_arg_value(cw->arena, proc, proc->i + 2 + widht, \
			(REG_CODE + RELATIVE))) : ft_itoa(arg)));
	}
	else if (proc->opcode == 2 || proc->opcode == 3 || proc->opcode == 13)
	{
		dst = ft_strjoin(dst, (((encoding & 0b00110000) >> 4) == REG_CODE ? \
			ft_strjoin("r", ft_itoa(arg)) : ft_itoa(arg)));
	}
	else
	{
		dst = ft_strjoin_1sp(dst, (((encoding & 0b00110000) >> 4) == REG_CODE \
			? ft_strjoin("r", ft_itoa(arg)) : ft_itoa(arg)));
	}
	return (dst);
}

char		*arg2_3_str(t_cw *cw, t_process *proc, char *dst, u_int8_t encoding)
{
	int			arg;
	int			widht;
	extern t_op	op_tab[17];

	if (op_tab[proc->opcode - 1].n_arg >= 2)
	{
		widht = instruction_width(cw->arena[(proc->i + 1) % MEM_SIZE] \
			& 0b11000000, op_tab[proc->opcode - 1]);
		arg = (cw->arena[(proc->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
		arg = get_arg_value(cw->arena, proc, proc->i + 2 + widht, arg);
		dst = arg2_into_str(cw, proc, dst, arg);
	}
	dst = arg3_str(cw, proc, dst, encoding);
	return (dst);
}

char		*arg_into_str(t_cw *cw, t_process *proc, char *dst, int arg)
{
	u_int8_t	encoding;
	int			a;

	encoding = cw->arena[(proc->i + 1) % MEM_SIZE];
	if (proc->opcode == 10 || proc->opcode == 8)
	{
		a = (proc->opcode == 10) ? proc->i + 1 : proc->i + 2;
		dst = ft_strjoin_1sp("", (((encoding & 0b11000000) >> 6) == REG_CODE ? \
			ft_itoa(get_arg_value(cw->arena, proc, a, \
			(REG_CODE + RELATIVE))) : ft_itoa(arg)));
	}
	else if (proc->opcode == 1 || proc->opcode == 15 || proc->opcode == 16 \
		|| proc->opcode == 12)
	{
		dst = ft_strjoin("", (((encoding & 0b11000000) >> 6) == REG_CODE ?\
			ft_strjoin("r", ft_itoa(arg)) : ft_itoa(arg)));
	}
	else
	{
		dst = ft_strjoin_1sp("", (((encoding & 0b11000000) >> 6) == REG_CODE ?\
			ft_strjoin("r", ft_itoa(arg)) : ft_itoa(arg)));
	}
	return (dst);
}

char		*args_to_str(t_cw *cw, t_process *proc)
{
	char		*dst;
	u_int8_t	encoding;
	int			arg;
	extern t_op	op_tab[17];

	arg = 0;
	encoding = cw->arena[(proc->i + 1) % MEM_SIZE];
	dst = NULL;
	if (op_tab[proc->opcode - 1].n_arg >= 1)
	{
		if (opcode_no_encoding(proc->opcode))
			arg = get_arg_value(cw->arena, proc, proc->i + 1, DIR_CODE);
		else
		{
			arg = ((encoding & 0b11000000) >> 6);
			arg = get_arg_value(cw->arena, proc, proc->i + 2, \
					(arg == IND_CODE) ? arg + RELATIVE : arg);
		}
		dst = arg_into_str(cw, proc, dst, arg);
	}
	dst = arg2_3_str(cw, proc, dst, encoding);
	return (dst);
}
