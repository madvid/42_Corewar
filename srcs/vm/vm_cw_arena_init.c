/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_cw_arena_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:02:34 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/16 01:38:26 by mdavid           ###   ########.fr       */
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

static void		load_champions(char **arena, t_champ *chp, int nb_champ)
{
	int		mem_pos;

	mem_pos = ((int)MEM_SIZE / nb_champ) * (chp->id - 1);
	ft_strcpy(*arena + mem_pos, chp->bytecode);
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
	char	*tmp;

	xplr = p->lst_champs;
	printf("ici 1\n");
	if (!(tmp = ft_strnew(MEM_SIZE)))
		return (0);
	printf("ici 2\n");
	while (xplr)
	{
		load_champions(&tmp, (t_champ*)(xplr->cnt), p->nb_champ);
		xplr = xplr->next;
	}
	printf("ici 3\n");
	return (1);
}

static int	vm_init_arena_memalloc(t_cw **cw, int nb_champ)
{
	if (!(*cw = (t_cw*)ft_memalloc(sizeof(t_cw))))
		return (0); //<- build vm_init_cw_error (vm_error_manager.c)
	if (!((*cw)->arena = ft_strnew(MEM_SIZE)))
		return (0); //<- vm_init_cw_error (vm_error_manager.c) avec un code error pour free les variables deja allouees
	if (!((*cw)->cursors = ft_lstnew(NULL, sizeof(t_cursor))))
		return (0); //<- idem
	while (nb > 0)
	{	
		ft_lstadd((*cw)->cursors, ft_lstnew(NULL, sizeof(t_cursor)));
		nb--;
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
	if (arena_and_champions_placement(cw->arena), p) == 0)
		return (0);
	return (1);
}
