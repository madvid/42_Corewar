/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_champion_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:02:30 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/19 10:35:25 by armajchr         ###   ########.fr       */
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

t_list		*reconstruct_champ_list(t_list **tab_champ, int nb_champ)
{
	int		i;

	i = 0;
	while (i + 1 < nb_champ)
	{
		tab_champ[i]->next = tab_champ[i + 1];
		i++;
	}
	tab_champ[i]->next = NULL;
	return (tab_champ[0]);
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
	t_list			**chp;
	int				nb_champ;
	int				i;
	int				id;

	if (ft_lst_len(*champ) == -1)
		return (-1);
	if (ft_lst_len(*champ) == 1)
		return (0);
	nb_champ = ft_lst_len(*champ);
	if (!(chp = (t_list**)malloc(sizeof(t_list*) * nb_champ)))
		return (-1);
	// ================================
	// id = 0;
	// i = 0;
	// while (++id <= 4)
	// {
	// 	xplr = get_champ_id(champ, id);
	// 	if (xplr != NULL)
	// 		chp[i++] = xplr;
	// }
	// ================================
	id = 4;
	i = 0;
	while (id-- > 0)
	{
		xplr = get_champ_id(champ, id);
		if (xplr != NULL)
			chp[i++] = xplr;
	}
	// ================================
	*champ = reconstruct_champ_list(chp, nb_champ);
	return (1);
}

/*
** Function: champ_name_via_id
** Description:
**	Looks the champion with the given ID and returns it name.
** Return:
** name: the name of the champion associated with the ID
** NULL: if no champion exists with the given ID
*/

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

/*
** Function: champ_via_id
** Description:
**	Looks the champion with the given ID and returns it.
** Return:
** champ: the link of the champion associated with the ID
** NULL: if no champion exists with the given ID
*/

t_champ		*champ_via_id(t_list *lst_champs, int id)
{
	t_list		*xplr;

	if (lst_champs == NULL)
		return (NULL);
	xplr = lst_champs;
	while(xplr)
	{
		if (((t_champ*)(xplr->cnt))->id == id)
			return ((t_champ*)(xplr->cnt));
		xplr = xplr->next;
	}
	return (NULL);
}


