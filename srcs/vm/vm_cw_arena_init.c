/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_cw_arena_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:02:34 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/21 15:08:24 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

/*
** Function: load_champions
** Description:
**	Loads the bytcode of the champion in parameter at the correct position.
**	The correct position is the beginning of the memory area associated with
**	the current champion, it depends on the amount of champions and the id of
**	the champion.
**	The memory areas are determined as: MEM_SIZE / nb_champ.
** Return:
**	1: if loading went well.
**	0: otherwise (mem. allocation issue).
*/

static int		load_champions(char **arena, t_champ *chp, int nb_champ)
{
	int			mem_pos;
	static int	t_mem_pos[4] = {-1, -1, -1, -1};
	int			i;

	i = -1;
	mem_pos = ((int)MEM_SIZE / nb_champ) * (chp->id - 1) % (int)MEM_SIZE;
	if (mem_pos != t_mem_pos[0] && mem_pos != t_mem_pos[1]
		&& mem_pos != t_mem_pos[2] && mem_pos != t_mem_pos[3])
		t_mem_pos[chp->id - 1] = mem_pos;
	else
		while ((mem_pos == t_mem_pos[0] || mem_pos == t_mem_pos[1]
		|| mem_pos == t_mem_pos[2] || mem_pos == t_mem_pos[3]) && ++i < 5)
			mem_pos = ((int)MEM_SIZE / nb_champ) * (chp->id + i - 1)
			% (int)MEM_SIZE;
	ft_memcpy((void*)(*arena + mem_pos), (void*)(chp->bytecode),
	(size_t)chp->l_bytecode);
	return (mem_pos);
}

/*
** Function:
** Description:
**	Allocates the memory of the arena and loading of the bytecode of the
**	differents champions.
** Return:
**	1: if no memory allocation issue.
**	0: otherwise.
*/

static int		arena_and_champions_placement(char **arena, t_parse *p)
{
	t_list	*xplr;

	xplr = p->lst_champs;
	while (xplr)
	{
		((t_champ*)(xplr->cnt))->mem_pos = load_champions(arena,
		(t_champ*)(xplr->cnt), p->nb_champ);
		xplr = xplr->next;
	}
	return (1);
}

/*
** Function: vm_init_cw_registers
** Description:
**	Allocation and initialization of the processes within cw struct.
**	-> Allocation part:
**		Memory allocation is performed for the processes struct and
**		registers, each process has 16 registers available.
**	-> Initialization part:
**		- id = processus id, unique for each process
**		- carry = initialized to false
**		- opcode = initialized to -1
**		- last_live = initialized to 0
**		- wait_cycles = initialized to 0
**		- position = memory adress of the beginning of the champion
**		- jump = initialized to 0
**		- registers[x]: small amount of memory reserve for each process
**		  /!\ r1 is initialized to the champion id.
**		- champ = pointer on the champion to facilitate the access of it inner
**		  variables
** Return:
**	1: if no memory allocation issue.
**	0: [via vm_init_cw_error] otherwise.
*/

static void			*vm_init_cw_registers(t_champ *champ, t_cw **cw)
{
	int				i;
	t_process		*proc;
	static int		proc_id;

	if (!(proc = (t_process*)ft_memalloc(sizeof(t_process))))
		return (vm_init_cw_error(3, cw) == 0 ? NULL : NULL);
	if (!(proc->registers = (char**)ft_memalloc(sizeof(char*) * (REG_NUMBER + 1))))
		return (vm_init_cw_error(3, cw) == 0 ? NULL : NULL);
	i = -1;
	while (++i < 16)
		if (!(proc->registers[i] = ft_strnew(REG_SIZE)))
			return (vm_init_cw_error(4, cw) == 0 ? NULL : NULL);
	if (!(proc->pc = ft_strnew(REG_SIZE)))
		return (vm_init_cw_error(4, cw) == 0 ? NULL : NULL);
	proc->registers[0][3] = champ->id & 255;
	proc->pc = NULL;
	proc->jump = 0;
	proc->id = ++proc_id;
	proc->carry = false;
	proc->opcode = 0;
	proc->last_live = 0;
	proc->wait_cycles = 0;
	proc->position = (void*)(&((*cw)->arena[champ->mem_pos]));
	proc->champ = champ;
	return ((void*)proc);
}

/*
** Function: vm_init_cw_memalloc
** Description:
**	Allocations of the inner variables of cw (corewar struct) which need memory allocation.
**	Exception for the processes which are allocated in vm_init_cw_registers function.
**	If there is a allocation memory issue, the error manager for the cw struct is in charge
**	of freeing the memory and print a message about this memory issue.
** Return:
**	1: if no memory allocation issue.
**	0: [via vm_init_cw_error] otherwise.
*/

static int		vm_init_cw_memalloc(t_cw **cw, int nb_champ)
{
	t_list		*tmp;

	tmp = NULL;
	if (!(*cw = (t_cw*)ft_memalloc(sizeof(t_cw))))
		return (vm_init_cw_error(0, cw));
	if (!((*cw)->arena = ft_strnew(MEM_SIZE)))
		return (vm_init_cw_error(1, cw));
	(*cw)->process = NULL;
	// if (!((*cw)->process = ft_lstnew(NULL, sizeof(t_process))))
	//	return (vm_init_cw_error(2, cw));
	while (nb_champ > 0)
	{
		if (!(tmp = ft_lstnew(NULL, sizeof(t_process))))
			return (vm_init_cw_error(3, cw));
		ft_lstadd(&(*cw)->process, tmp);
		nb_champ--;
	}
	(*cw)->cycle_to_die = CYCLE_TO_DIE;
	(*cw)->delta_cycle = CYCLE_DELTA;
	(*cw)->nb_lives = 0;
	(*cw)->inter_check = MAX_CHECKS;
	return (1);
}

/*
** Function: vm_cw_arena_init
** Description:
**	Creation and initialization of the arena:
**		- memory allocation of the arena,
**		- loading of bytecodes of the champions at the correct memory adresses,
**		- memory allocation + initialization of inner variables of the processes.
** Return:
**	1: If arena, champions loading or registers creation is ok.
**	0: otherwise (memory allocation issue at some point).
*/

int				vm_cw_arena_init(t_cw **cw, t_parse **p)
{
	t_list		*xplr;
	t_list		*xplr2;

	xplr = (*p)->lst_champs;
	if (!(vm_init_cw_memalloc(cw, (*p)->nb_champ)))
		return (vm_init_parse_error(4, p));
	if (arena_and_champions_placement(&((*cw)->arena), *p) == 0)
		return (vm_init_parse_error(4, p));
	xplr2 = (*cw)->process;
	while (xplr)
	{
		xplr2->cnt = vm_init_cw_registers((t_champ*)xplr->cnt, cw);
		if (!(xplr->cnt))
			return (vm_init_parse_error(4, p));
		xplr = xplr->next;
		xplr2 = xplr2->next;
	}
	return (1);
}
