/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_cw_arena_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:02:34 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/15 18:51:22 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void		load_champions(void *arena, t_champ *chp, int nb_champ)
{
	int		mem_pos;

	mem_pos = ((int)MEM_SIZE / nb_champ) * (chp->id - 1);
	ft_memcpy(arena + mem_pos, (void*)chp->bytecode, (size_t)chp->l_bytecode);
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

static int		arena_and_champions_placement(t_cw *cw, t_parse *p)
{
	t_list	*xplr;

	xplr = p->lst_champs;
	if (!(cw->arena = ft_memalloc(MEM_SIZE)))
		return (0);
	while (xplr)
	{
		load_champions(cw->arena, (t_champ*)(xplr->cnt), p->nb_champ);
		xplr = xplr->next;
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

int				vm_cw_arena_init(t_cw *cw, t_parse *p)
{
	if (arena_and_champions_placement(cw, p) == 0)
		return (0);
	return (1);
}
