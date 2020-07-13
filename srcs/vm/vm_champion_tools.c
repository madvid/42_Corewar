/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champion_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:49:06 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/13 16:41:06 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "vm.h"

/*
** Function: attribut_nb_champ
**
**
*/
static int	attribut_nb_champ(t_list* lst_champ)
{
	t_list		*xplr;
	int			i;
	int			id;
	
	i = 0;
	id = 1;
	if (!lst_champ)
		return (1);
	while (i < 4)
	{
		xplr = lst_champ;
		while (xplr)
		{
			if (id == ((t_champ*)(xplr->cnt))->id)
			{
				id++;
				break;
			}
			xplr = xplr->next;
		}
		i++;
	}
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

int 		is_valid_champ_filename(char* filename)
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

static int	set_champ_value(t_champ *champ, t_parse *p, char *str, int attr_nb)
{
		champ->id = (p->options->n > 0) ? p->id_champ : attr_nb;
		if (!(champ->champ_file = ft_strdup(str))
			|| !(champ->name = ft_strdup("name"))
			|| !(champ->comment = ft_strdup("comment")))
			{
				ft_strdel(&(champ->champ_file));
				ft_strdel(&(champ->name));
				ft_strdel(&(champ->comment));
				return (0);
			}
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

	if (is_valid_champ_filename(av))
	{
		nw_link = NULL;
		if (set_champ_value(&champ, p, av, attribut_nb_champ(*lst_champs)) == 0)
			return (0);
		if (!(nw_link = ft_lstnew(&champ, sizeof(champ))))
			return (0); // mem alloc of the new link failed.
		ft_lstadd(lst_champs, nw_link);
		p->nb_champ++;
		return (1);
	}
	// Either there is no av[i + 1], or the filename is not valid or mem issue for the link
	return (0);
}