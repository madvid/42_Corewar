/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_opcode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:35:15 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/24 11:25:38 by mdavid           ###   ########.fr       */
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
**	Checks the validity of the encoded byte (if there is one) associated to
**	the opcode in the current process and performs the corresponding
**	instruction if wait_cycles of the process is 0.
** Return:
**	0: No error has been raised by any opcode functions (by return -1)
**	code_error: Can only be an memory allocation issue during process creation
*/

int		perform_opcode(t_cw *cw, t_process *cur_proc)
{
	int				code_error;
	extern t_op		op_tab[17];
	static int		(*op_funct[16])(t_cw*, t_process*) = {NULL};

	code_error = 0;
	if (op_funct[0] == NULL)
		init_op_funct(op_funct);
	if (cur_proc->wait_cycles == 0)
	{
		// cur_proc->pc = addr_next_opcode(cw->arena, cur_proc);
		if (!is_valid_opcode(cw, cw->arena, cur_proc))
			return (0);
		if (cur_proc->opcode == 12 || cur_proc->opcode == 15)
			code_error = (op_funct[cur_proc->opcode - 1](cw, cur_proc) == -1) ? CD_PROC_MEM : 0;
		else
			op_funct[cur_proc->opcode - 1](cw, cur_proc);
	}
	return (code_error);
}

/*
** Function: is_opcode
** Description:
**	[put some explanations here]
** Return:
**	1: if the byte is an opcode.
**	0: if the byte does not correspond to an opcode.
*/

bool	is_valid_opcode(t_cw *cw, char *arena, t_process *cur_proc)
{
	u_int8_t	opcode;
	u_int8_t	encoding;
	int			widht;
	extern t_op	op_tab[17];

	// opcode = arena[cur_proc->i];
	opcode = cur_proc->opcode;
	if (opcode_no_encoding(opcode))
		return (true);
	if (opcode >= 1 && opcode <= 16)
	{
		encoding = (u_int8_t)arena[(cur_proc->i + 1) % (int)MEM_SIZE];
		if (is_valid_encoding(opcode, encoding) == false)
		{
			widht = 0;
			if (opcode == 3 || opcode == 11)
				widht = instruction_width(cw->arena[(cur_proc->i) % MEM_SIZE], op_tab[cur_proc->opcode - 1]) + 6;
			else
				widht = instruction_width(cw->arena[(cur_proc->i) % MEM_SIZE], op_tab[cur_proc->opcode - 1]);
			(cw->options->v_lvl & 16) ? vprint_pcmv(cw, cur_proc, widht) : 0;
			return (false);
		}
		if (is_valid_reg(arena, cur_proc) == false)
		{
			widht = 0;
			if (opcode == 3 || opcode == 11)
				widht = instruction_width(cw->arena[(cur_proc->i) % MEM_SIZE], op_tab[cur_proc->opcode - 1]) + 6;
			else
				widht = instruction_width(cw->arena[(cur_proc->i) % MEM_SIZE], op_tab[cur_proc->opcode - 1]);
			(cw->options->v_lvl & 16) ? vprint_pcmv(cw, cur_proc, widht) : 0;
			return (false);
		}
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

// ---> origine
// int		addr_next_opcode(char *arena, int mem_pos)
// {
// 	u_int8_t	encoding;
// 	u_int8_t	opcode;
// 	int			next_opcode;
// 	extern t_op	op_tab[17];

// 	opcode = (u_int8_t)arena[mem_pos];
// 	if (opcode_no_encoding(opcode))
// 	{
// 		next_opcode = (mem_pos + arg_size_opcode_no_encode(opcode) + 1) % MEM_SIZE;
// 		return (next_opcode);
// 	}
// 	if (opcode > 0 && opcode < 17) // ici, comme on a tester les opcode sans byte d'encodage, ça sera les autres traités ici.
// 	{
// 		encoding = (u_int8_t)arena[(mem_pos + 1) % MEM_SIZE];
// 		next_opcode = instruction_width(encoding, op_tab[opcode - 1]) + 2;
// 		return ((mem_pos + next_opcode) % MEM_SIZE);
// 	}
// 	return ((mem_pos + 1) % MEM_SIZE);
// }

/// ----> proposition 1
int		addr_next_opcode(char *arena, t_process *proc)
{
	u_int8_t	encoding;
	u_int8_t	opcode;
	int			next_opcode;
	extern t_op	op_tab[17];

	opcode = proc->opcode;
	if (opcode_no_encoding(opcode))
	{
		next_opcode = (proc->i + arg_size_opcode_no_encode(opcode) + 1) % MEM_SIZE;
		return (next_opcode);
	}
	if (opcode > 0 && opcode < 17) // ici, comme on a tester les opcode sans byte d'encodage, ça sera les autres traités ici.
	{
		encoding = (u_int8_t)arena[(proc->i + 1) % MEM_SIZE];
		next_opcode = instruction_width(encoding, op_tab[opcode - 1]) + 2;
		return ((proc->i + next_opcode) % MEM_SIZE);
	}
	return ((proc->i + 1) % MEM_SIZE);
}