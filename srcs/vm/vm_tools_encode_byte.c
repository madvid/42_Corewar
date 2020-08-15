/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_encode_byte.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:35:12 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/15 20:36:05 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function:
** Description:
**	Functions analyses the encoding byte to know how many arguments are given.
** Remarks:
**	Function may seems unecessary as knowing the opcode allow us to know how
**	many arguments we should found, but if there is a mistake, we will know it
** Return:
**	1/2/3 : the number of arguments of opcode based on encode byte.
**	-1	  : if 
*/

int		get_nb_arg_b_encoding(u_int8_t encoding)
{
	u_int8_t		l_arg[4];

	l_arg[0] = (encoding & 0b11000000) >> 6;
	l_arg[1] = (encoding & 0b00110000) >> 4;
	l_arg[2] = (encoding & 0b00001100) >> 2;
	l_arg[3] = (encoding & 0b00000011);
	// printf("    [get_nb_arg] valeur de encoding = %d\n", (int)encoding);
	// printf("    [get_nb_arg] valeur de l_arg[0] = %d\n", l_arg[0]);
	// printf("    [get_nb_arg] valeur de l_arg[1] = %d\n", l_arg[1]);
	// printf("    [get_nb_arg] valeur de l_arg[2] = %d\n", l_arg[2]);
	// printf("    [get_nb_arg] valeur de l_arg[3] = %d\n", l_arg[3]);
	if (l_arg[0] && !l_arg[1] && !l_arg[2] && !l_arg[3])
		return (1);
	if (l_arg[0] && l_arg[1] && !l_arg[2] && !l_arg[3])
		return (2);
	if (l_arg[0] && l_arg[1] && l_arg[2] && !l_arg[3])
		return (3);
	return (0);
}

/*
** Function: is_valid_encoding
** Description:
**	Function verifies the encoding byte according to the opcode.
**	Firstly, the number of arguments is determined (stocked in l_arg[0]) and
**	compares with the number of arguments the opcode must have.
**	Then, the type of each argument is compare with what it is exepected as
**	argument type for the opcode.
** Return:
**	true : If nb of arg and type fit perfectly with what it is expected.
**	false: if the number of arg or one of the argument type does not correspond
**		   with what it is expected.
*/

bool	is_valid_encoding(u_int8_t opcode, u_int8_t encoding)
{
	extern	t_op	op_tab[17];
	int				l_arg[5];
	int				i;

	i = 1;
	l_arg[0] = get_nb_arg_b_encoding(encoding);
	l_arg[1] = (encoding & 0b11000000) >> 6;
	l_arg[2] = (encoding & 0b00110000) >> 4;
	l_arg[3] = (encoding & 0b00001100) >> 2;
	l_arg[4] = (encoding & 0b00000011);
	// printf("      [is_valid_encoding] l_arg[0] = %d\n", l_arg[0]);
	// printf("      [is_valid_encoding] l_arg[1] = %d\n", l_arg[1]);
	// printf("      [is_valid_encoding] l_arg[2] = %d\n", l_arg[2]);
	// printf("      [is_valid_encoding] l_arg[3] = %d\n", l_arg[3]);
	if (l_arg[0] != (int)op_tab[(int)opcode - 1].n_arg)
		return (false);
	while (i < (int)op_tab[(int)opcode - 1].n_arg)
	{
		if ((l_arg[i] & (int)op_tab[(int)opcode - 1].type[i - 1]) == 0)
			return (false);
		i++;
	}
	return (true);
}

char		*arg2_3_to_str(t_cw *cw, t_process *proc, char *dst, u_int8_t encoding)
{
	int			arg;
	int			widht;
	extern t_op	op_tab[17];
	
	if (op_tab[proc->opcode - 1].n_arg >= 2)
	{
		widht = instruction_width(cw->arena[(proc->i + 1) % MEM_SIZE] \
			& 0b11000000, op_tab[proc->opcode - 1].direct_size);
		ft_printf("    [ARG2_3_TO_STR]: widht = %d\n", widht);
		arg = (cw->arena[(proc->i + 1) % MEM_SIZE] & 0b00110000) >> 4;
		ft_printf("    [ARG2_3_TO_STR]: type 2nd arg = %d\n", arg);
		arg = get_arg_value(cw->arena, proc, proc->i + 2 + widht, (arg == IND_CODE) ? arg + RELATIVE : arg);
		ft_printf("    [ARG2_3_TO_STR]: val 2nd arg = %d\n", arg);
		dst = ft_strjoin_1sp(dst, (((encoding & 0b00110000) >> 4) == REG_CODE ? \
			ft_strjoin("r", ft_itoa(arg)) : ft_itoa(arg)));
	}
	if (op_tab[proc->opcode - 1].n_arg >= 3)
	{
		widht = instruction_width(cw->arena[(proc->i + 1) % MEM_SIZE] \
			& 0b11110000, op_tab[proc->opcode - 1].direct_size);
		arg = (cw->arena[(proc->i + 1) % MEM_SIZE] & 0b00001100) >> 2;
		arg = get_arg_value(cw->arena, proc, proc->i + 2 + widht, (arg == IND_CODE) ? arg + RELATIVE : arg);
		dst = ft_strjoin_1sp(dst, (((encoding & 0b00001100) >> 2) == REG_CODE ? \
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
	if (proc->opcode == 3)
	{
		ft_printf("    ici1\n");
		tool_print_processor(proc, 0);
	}
	if (op_tab[proc->opcode - 1].n_arg >= 1)
	{
		if (opcode_no_encoding(proc->opcode))
			arg = get_arg_value(cw->arena, proc, proc->i + 1, DIR_CODE);
		else
		{
			arg = ((encoding & 0b11000000) >> 6) & 255;
			ft_printf("    [ARGS_TO_STR]: type 1er arg = %d\n", arg);
			arg = get_arg_value(cw->arena, proc, proc->i + 2, (arg == IND_CODE) ? arg + RELATIVE : arg);
			ft_printf("    [ARGS_TO_STR]: val 1er arg = %d\n", arg);
		}
		dst = ft_strjoin_1sp("", (((encoding & 0b11000000) >> 6) == REG_CODE ? \
			ft_strjoin("r", ft_itoa(arg)) : ft_itoa(arg)));
	}
	dst = arg2_3_to_str(cw, proc, dst, encoding);
	return (dst);
}