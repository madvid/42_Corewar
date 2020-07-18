/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champion_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:49:06 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/18 22:17:14 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

/*
** Function: attribut_nb_champ
** Description:
**	Function explores the int table of id, to find an available one.
**	An id is available if id_table[id -1] is equal to 0.
** Return:
**	id: the available id for the new champion.
**	0: otherwise.
*/

static int	attribut_nb_champ(int *id_table)
{
	int		id;

	id = 1;
	while (id < 5 && id_table[id - 1] == 1)
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
*/

static int	set_champ_value(t_champ *champ, t_parse *p, char *str)
{
	if (p->options->n == 1)
	{
		champ->id = p->id_champ;
		p->id_table[champ->id - 1] = 1;
	}
	else
	{
		champ->id = attribut_nb_champ(p->id_table);
		p->id_table[champ->id - 1] = 1;
	}
	if (!(champ->champ_file = ft_strdup(str)))
		return (0);
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
		return (0);
	if (!(nw_link = ft_lstnew(&champ, sizeof(champ))))
		return (0);
	ft_lstadd(lst_champs, nw_link);
	p->nb_champ++;
	p->options->n = 0;
	p->id_champ = 0;
	return (1);
}
