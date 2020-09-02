/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 16:27:21 by armajchr          #+#    #+#             */
/*   Updated: 2020/09/02 16:40:14 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: instruction_width
** Description:
**	Reads the encoding byte and calculates the length in bytes of the arguments
**	field.
** Remarks:
**	Each arg can take 4 values:
**		ag_1: can be 192/128/64 depending if 11/10/01 (xx 00 00 00).
**		ag_2: can be 48/32/16 depending if 11/10/01 (00 xx 00 00).
**		ag_3: can be 12/8/4 depending if 11/10/01 (00 00 xx 00).
** Reminder:
**	In the encoding byte are present the type of the different arguments:
**		11 means the argument is an indirect type (2 bytes long),
**		10 means the argument is an direct type (4 bytes long),
**		01 means the argument is an indirect type (1 byte long)
** Return
**	width: total length in term of bytes of the different parameters of opcode.
**	0: if the encoding byte is invalid.
*/

int		instruction_width(unsigned char encoding, t_op op_elem)
{
	u_int8_t	ag_1;
	u_int8_t	ag_2;
	u_int8_t	ag_3;
	size_t		size_dir;
	int			width;

	width = 0;
	size_dir = (op_elem.direct_size == 1) ? 2 : 4;
	ag_1 = (encoding & 0b11000000) >> 6;
	ag_2 = (encoding & 0b00110000) >> 4;
	ag_3 = (encoding & 0b00001100) >> 2;
	if (ag_1 != 0 && op_elem.n_arg >= 1)
		width += (ag_1 == 2) ? (int)size_dir : 2 * (ag_1 / 3) + (1 - ag_1 / 2);
	if (ag_2 != 0 && op_elem.n_arg >= 2)
		width += (ag_2 == 2) ? (int)size_dir : 2 * (ag_2 / 3) + (1 - ag_2 / 2);
	if (ag_3 != 0 && op_elem.n_arg >= 3)
		width += (ag_3 == 2) ? (int)size_dir : 2 * (ag_3 / 3) + (1 - ag_3 / 2);
	return (width);
}
