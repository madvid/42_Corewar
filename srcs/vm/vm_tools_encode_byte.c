/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_encode_byte.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:35:12 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/29 16:56:53 by mdavid           ###   ########.fr       */
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
	int				nb_arg;

	l_arg[0] = (encoding & 0b11000000) >> 6;
	l_arg[1] = (encoding & 0b00110000) >> 4;
	l_arg[2] = (encoding & 0b00001100) >> 2;
	l_arg[3] = (encoding & 0b00000011);
	printf("    [get_nb_arg] valeur de encoding = %d\n", (int)encoding);
	printf("    [get_nb_arg] valeur de l_arg[0] = %d\n", l_arg[0]);
	printf("    [get_nb_arg] valeur de l_arg[1] = %d\n", l_arg[1]);
	printf("    [get_nb_arg] valeur de l_arg[2] = %d\n", l_arg[2]);
	printf("    [get_nb_arg] valeur de l_arg[3] = %d\n", l_arg[3]);
	nb_arg = 0;
	nb_arg += (l_arg[0] > 0 && l_arg[0] < 4) ? 1 : -1;
	nb_arg += (nb_arg > 0 && l_arg[1] > 0 && l_arg[1] < 4) ? 1 : -2;
	nb_arg += (nb_arg > 0 && l_arg[2] > 0 && l_arg[2] < 4) ? 1 : -3;
	nb_arg += (nb_arg > 0 && l_arg[3] == 0) ? 0 : -4;
	return (nb_arg > 0 ? nb_arg : -1);
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
	printf("      [is_valid_encoding] l_arg[0] = %d\n", l_arg[0]);
	printf("      [is_valid_encoding] l_arg[1] = %d\n", l_arg[1]);
	printf("      [is_valid_encoding] l_arg[2] = %d\n", l_arg[2]);
	printf("      [is_valid_encoding] l_arg[3] = %d\n", l_arg[3]);
	if (l_arg[0] != (int)op_tab[(int)opcode].n_arg)
		return (false);
	while (i < (int)op_tab[(int)opcode].n_arg)
	{
		if ((l_arg[i] & (int)op_tab[(int)opcode].type[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}