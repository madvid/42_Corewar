/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_cw_arena_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:02:34 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/16 17:22:19 by mdavid           ###   ########.fr       */
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
**	
** Return:
**	1: if loading went well.
**	0: otherwise (mem. allocation issue).
*/

static void		*load_champions(char **arena, t_champ *chp, int nb_champ)
{
	int		mem_pos;

	mem_pos = ((int)MEM_SIZE / nb_champ) * (chp->id - 1);
	ft_memcpy((void*)(*arena + mem_pos), (void*)(chp->bytecode), (size_t)chp->l_bytecode);
	return ((void*)(*arena + mem_pos));
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
		((t_champ*)(xplr->cnt))->mem_pos = load_champions(arena, (t_champ*)(xplr->cnt), p->nb_champ);
		// tool_print_champ((t_champ*)(xplr->cnt));
		xplr = xplr->next;
	}
	return (1);
}

/*
** Function: vm_init_cw_registers
** Description:
**	Allocation and initialization of the cursors within cw struct.
**	-> Allocation part:
**		Memory allocation is performed for the cursors struct and
**		registers, each process has 16 registers available.
**	-> Initialization part:
**		- id = champion id to which the process is associated with,
**		- carry = initialized to false
**		- opcode = initialized to -1
**		- last_live = initialized to 0
**		- wait_cycles = initialized to 0
**		- position = memory adress of the beginning of the champion
**		- jump = initialized to 0
**		- registers[x]:
**		- adrchamp = memory adress of the link containing the champion
** Return:
**	1: if no memory allocation issue.
**	0: [via vm_init_cw_error] otherwise.
*/

static int		vm_init_cw_registers(t_cw **cw, t_list *lst_champs)
{
	int				i;
	t_cursor		*csr;

	
	if (!(csr = (t_cursor*)ft_memalloc(sizeof(t_cursor))))
		return (0); // <- redirriger vers error manager
	if (!(csr->registers = (void**)ft_memalloc(REG_NUMBER)))
		return (0); // <- redirriger vers error manager
	i = -1;
	while (++i < 16)
		if (!(csr->registers[i] = (void*)ft_memalloc(REG_SIZE)))
			return (0); // <- redirriger vers error manager

	return (1);
}

/*
** Function: vm_init_cw_memalloc
** Description:
**	Allocations of the inner variables of cw (corewar struct) which need memory allocation.
**	Exception for the cursors which are allocated in vm_init_cw_registers function.
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
		return (vm_init_cw_error(0, cw, nb_champ));
	if (!((*cw)->arena = ft_strnew(MEM_SIZE)))
		return (vm_init_cw_error(1, cw, nb_champ));;
	if (!((*cw)->cursors = ft_lstnew(NULL, sizeof(t_cursor))))
		return (vm_init_cw_error(2, cw, nb_champ));
	while (nb_champ > 0)
	{
		if (!(tmp = ft_lstnew(NULL, sizeof(t_cursor))))
			return (vm_init_cw_error(3, cw, nb_champ));
		ft_lstadd(&(*cw)->cursors, tmp);
		nb_champ--;
	}
	return (1);
}

/*
** Function: vm_cw_arena_init
** Description:
**	Creation and initialization of the arena:
**		- memory allocation of the arena,
**		- loading of bytecodes of the champions at the correct memory adresses,
**		- memory allocation + initialization of inner variables of the cursors.
** Return:
**	1: If arena, champions loading or registers creation is ok.
**	0: otherwise (memory allocation issue at some point).
*/

int				vm_cw_arena_init(t_cw **cw, t_parse *p)
{
	if (!(vm_init_cw_memalloc(cw, p->nb_champ)))
		return (0);
	if (!vm_init_cw_registers(cw, p->lst_champs))
		return (0);
	if (arena_and_champions_placement(&((*cw)->arena), p) == 0)
		return (0);
	
	return (1);
}
