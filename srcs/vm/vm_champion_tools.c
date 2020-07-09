/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champion_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:49:06 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/09 14:09:20 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

/*
**
**
**
*/

static int is_valid_champ_filename(char* filename)
{

}

/*
** Function: vm_create_champion
** Description:
**	Function checks if there is the filename in the next argument av, 
*/

int		vm_create_champion(t_list **lst_champs, char **av, int i)
{
	t_list		*nw_link;
	t_champ		*champ;

	if (av[i] && av[i + 1] && is_valid_champ_filename(av[i + 1]))
	{
		nw_link = NULL;
		champ->id = ft_atoi(av[i]);
		champ->champ_file = av[i + 1];
		nw_link = ft_lstnew(champ, sizeof(champ));
		ft_lstadd(lst_champs, nw_link);
	}
	else
	{
		// Either there is no av[i + 1], or the filename is not valid or mem issue for the link
		return (0)
	}
	return (1);
}