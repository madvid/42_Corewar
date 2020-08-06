/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_opcode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:35:15 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/05 10:45:08 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_op_funct(int (**t_op_funct)(t_cw*, t_process*))
{
	t_op_funct[0] = &op_alive;
	t_op_funct[1] = &op_load;
	t_op_funct[2] = &op_store;
	t_op_funct[3] = &op_addition;
	t_op_funct[4] = &op_soustraction;
	t_op_funct[5] = &op_and;
	t_op_funct[6] = &op_or;
	t_op_funct[7] = &op_xor;
	t_op_funct[8] = &op_zerojump;
	t_op_funct[9] = &op_load_index;
	t_op_funct[10] = &op_store_index;
	 t_op_funct[11] = &op_fork;
	t_op_funct[12] = &op_long_load;
	t_op_funct[13] = &op_long_load_index;
	t_op_funct[14] = &op_long_fork;
	t_op_funct[15] = &op_aff;
}

/*
** Function: perform_opcode
** Description:
**	[put some explanations here !]
*/

void	perform_opcode(t_cw *cw, t_process *cur_proc)
{
	extern t_op		op_tab[17];
	int				ret;
	static int		(*op_funct[16])(t_cw*, t_process*) = {NULL};

	
	if (op_funct[0] == NULL)
		init_op_funct(op_funct);
	if (cur_proc->wait_cycles == 0)
	{
		// printf("[perform_opcode] is_valid_opcode = %d\n", is_valid_opcode(cw->arena, cur_proc));
		// printf("[perform_opcode] valeur pointée par processor = %d\n", (int)cw->arena[cur_proc->i]);
		// printf("[perform_opcode] valeur du byte d'encodage = %d\n", (int)cw->arena[cur_proc->i + 1]);
		if (!is_valid_opcode(cw->arena, cur_proc))
			return ;
		ret = op_funct[cur_proc->opcode - 1](cw, cur_proc);
		// if (ret == 0 && (cw->options->verbose & xx)) <- definir le niveau de verbose
		// 	ft_printf("P-%d: instruction %d(%s) incorrect\n", cur_proc->id, op_tab[cur_proc->opcode - 1].name);
		// if (ret == -1)
		// 	return (vm_error_manager(, cw));
	}
}

/*
** Function: is_opcode
** Description:
**	[put some explanations here]
** Return:
**	1: if the byte is an opcode.
**	0: if the byte does not correspond to an opcode.
*/

bool	is_valid_opcode(char *arena, t_process *cur_proc)
{
	u_int8_t	opcode;
	u_int8_t	encoding;

	opcode = arena[cur_proc->i];
	if (opcode_no_encoding(opcode))
		return (true);
	if (opcode >= 1 && opcode <= 16)
	{
		encoding = (u_int8_t)arena[(cur_proc->i + 1) % (int)MEM_SIZE];
		if (is_valid_encoding(opcode, encoding) == false)
			return (false);
		if (is_valid_reg(arena, cur_proc) == false)
			return (false);
		return (true);
	}
	return (false);
}

/*
** Function: arg_size_opcode_no_encode
** Description:
**	[put some explanation here]
** Return:
**	4: length of the argument of the instruction live (opcode = 1).
**	1: length of the argument of zjmp/fork/lfork (opcode 9/12/15).
**	-1: if the opcode value is not within (1 ; 9 ; 12 ; 15)
*/

int		arg_size_opcode_no_encode(u_int8_t opcode)
{
	if (opcode == 1)
		return (4);
	if (opcode == 9)
		return (2);
	if (opcode == 12)
		return (2);
	if (opcode == 15)
		return (2);
	return (-1);
}

/*
** Function: opcode_no_encoding
** Description:
**	Checks if the opcode is one of those without encoding byte.
** Return:
**	true: if opcode does not have encoding byte.
**	false: otherwise
*/

bool	opcode_no_encoding(u_int8_t opcode)
{
	if (opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15)
		return (true);
	else
		return (false);
}


/*
** Function: addr_next_opcode
** Description:
**	Gets the address of the next opcode, without distinguish if the opcode is
**	related to the 'current' champion.
** Return:
**	addr: address of the next opcode.
**	NULL: there is no next opcode right after the ongoing one.
*/

int		addr_next_opcode(char *arena, int mem_pos)
{
	u_int8_t	encoding;
	u_int8_t	opcode;
	int			next_opcode;
	extern t_op	op_tab[17];

	opcode = (u_int8_t)arena[mem_pos];
	if (opcode_no_encoding(opcode))
	{
		next_opcode = (mem_pos + arg_size_opcode_no_encode(opcode) + 1) % MEM_SIZE;
		return (next_opcode);
	}
	if (opcode > 0 && opcode < 17) // ici, comme on a tester les opcode sans byte d'encodage, ça sera les autres traités ici.
	{
		encoding = (u_int8_t)arena[(mem_pos + 1) % MEM_SIZE];
		next_opcode = instruction_width(encoding, op_tab[opcode - 1].direct_size) + 2;
		return ((mem_pos + next_opcode) % MEM_SIZE);
	}
	return ((mem_pos + 1) % MEM_SIZE);
}
