/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_champion_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:02:30 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/15 17:59:17 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: reconstruct_champ_list
** Description:
**	Functions cuts the links and relinks the champions.
** Return:
**	new: the sorted list of champions
*/

t_list		*reconstruct_champ_list(t_list *tab_champ[4])
{
	t_list	*new;
	int		i;
	int		stat;

	i = 0;
	stat = 0;
	while (i <= 4)
	{
		if (tab_champ[i])
		{
			tab_champ[i]->next = NULL;
			if (stat == 0)
			{
				new = tab_champ[i];
				stat++;
			}
			else
			{
				ft_lstaddend(&new, tab_champ[i]);
			}
		}
		i++;
	}
	return (new);
}

/*
** Function: get_champ_id
** Description:
**	Searchs and return the address link of the champion with the corresponding
**	id.
** Return:
**	address of the champion : if the champion was found.
**	NULL: if the champion has not been found.
*/

t_list		*get_champ_id(t_list **champ, int id)
{
	t_list	*xplr;

	if (!champ || !(xplr = *champ))
		return (NULL);
	while (xplr)
	{
		if (((t_champ*)(xplr->cnt))->id == id)
			return (xplr);
		xplr = xplr->next;
	}
	return (NULL);
}

/*
** Function: sort_champion
** Description:
**	Reconstructs and sorts the list of champions.
**	The goal is to sort champions in ascending ordering ID.
** Return:
**	1: the list has been sorted
**	0: if the list to sort is NULL
*/

int		lst_sort_champion(t_list **champ)
{
	t_list			*xplr;
	static t_list	*chp[4]={NULL, NULL, NULL, NULL};
	int				i;
	int				id;

	if (ft_lst_len(*champ) == -1)
		return (0);
	if (ft_lst_len(*champ) == 1)
		return (0);
	i = 0;
	id = 0;
	while (++id <= 4)
	{
		xplr = get_champ_id(champ, id);
		if (xplr != NULL)
			chp[i++] = xplr;
	}
	*champ = reconstruct_champ_list(chp);
	return (1);
}

char	*champ_name_via_id(t_list *lst_champs, int id)
{
	t_list		*xplr;

	if (lst_champs == NULL)
		return (NULL);
	xplr = lst_champs;
	while(xplr)
	{
		if (((t_champ*)(xplr->cnt))->id == id)
			return (((t_champ*)(xplr->cnt))->name);
		xplr = xplr->next;
	}
	return (NULL);
}

