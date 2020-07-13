/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champion_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:49:06 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/12 22:32:50 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	
	i = 1;
	if (!lst_champ)
		return (0);
	while (i < 4)
	{
		xplr = lst_champ;
		while (xplr)
		{
			if (i == ((t_champ*)(xplr->cnt))->id)
			{
				i++;
				break;
			}
			xplr = xplr->next;
		}
	}
	return (i);
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
	return (ft_strequ(filename + len - 3, ".cor"));
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
		champ.id = (p->options->n != 0) ? p->id_champ : attribut_nb_champ(*lst_champs);
		champ.champ_file = av;
		if (!(nw_link = ft_lstnew(&champ, sizeof(champ))))
			return (0); // mem alloc of the new link failed.
		ft_lstadd(lst_champs, nw_link);
		p->nb_champ = 0;
		return (1);
	}
	// Either there is no av[i + 1], or the filename is not valid or mem issue for the link
	return (0);
}