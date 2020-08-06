/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_champion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:49:06 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/06 15:35:57 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

/*
** Function: attribut_nb_champ
** Description:
**	Function explores the int table of id, to find an available one.
**	An id is available if id_available[id -1] is equal to 0.
** Return:
**	id: the available id for the new champion.
**	0: otherwise.
*/

static int	attribut_nb_champ(int *id_available)
{
	int		id;

	id = 1;
	while (id < 5 && id_available[id - 1] == 1)
		id++;
	if (id == 5)
		return (0);
	return (id);
}

/*
** Function: is_valid_champ_filename
** Description:
**	Function checks if the filename has the correct format, meaning extension
**	'.cor' is present.
** Return:
**	1: filename is acceptable
**	0: otherwise
*/

int			is_valid_champ_filename(char *filename)
{
	int		len;

	len = ft_strlen(filename);
	return (ft_strequ(filename + len - 4, ".cor"));
}

/*
** Function:
** Description:
**	Set the value of the champion before adding it into the link.
** Return:
**	1: attribution of id and copy of filename has been performed
**	0: file name is too long.
*/

static int	set_champ_value(t_champ *champ, t_parse *p, char *str)
{
	if (p->options->n == 1)
	{
		champ->id = p->id_champ;
		p->id_available[champ->id - 1] = 1;
	}
	else
	{
		champ->id = attribut_nb_champ(p->id_available);
		p->id_available[champ->id - 1] = 1;
	}
	if (ft_strlen(str) >= (int)FILE_BIG)
		return (0);
	champ->champ_file = str;
	champ->name = NULL;
	champ->comment = NULL;
	champ->l_bytecode = 0;
	champ->bytecode = NULL;
	champ->mem_pos = -1;
	return (1);
}

/*
** Function: vm_create_champion
** Description:
**	Function checks if there is the filename in the next argument av,
*/

int			vm_create_champion(t_list **lst_champs, char *av, t_parse *p)
{
	t_list		*nw_link;
	t_champ		champ;

	nw_link = NULL;
	if (set_champ_value(&champ, p, av) == 0)
		return ((int)CD_FILE_BIG);
	if (!(nw_link = ft_lstnew(&champ, sizeof(champ))))
		return ((int)CD_MEM_CHAMP);
	ft_lstadd(lst_champs, nw_link);
	p->nb_champ++;
	p->options->n = 0;
	p->id_champ = 0;
	return (0);
}

/*
** Function: vm_champion_introduction
** Description:
**	Introduces the different champions before the battle.
*/

void	vm_champion_introduction(t_list *lst_champs)
{
	t_list	*xplr;
	t_champ	*chp;
	int		id;

	xplr = lst_champs;
	ft_putstr("Introducing contestants...\n");
	while (xplr)
	{
		chp = (t_champ *)(xplr->cnt);
		id = chp->id;
		printf("* Player %d, weighing %d bytes,", id, chp->l_bytecode);
		printf(" \"%s\" (\"%s\") !\n", chp->name, chp->comment);
		xplr = xplr->next;
	}
}
