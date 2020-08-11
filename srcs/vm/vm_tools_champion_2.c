/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_champion_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:02:30 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/11 13:37:39 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: lst_order_chmp
** Description:
**	Checks if the id of the champion 1 (chp1) is lower than the id of champion
**	2 (chp2).
** Return:
**	1: if chp1->id > chp2->id
**	0: if not
**	-1: if one or both of the link received is/are NULL.
*/

int		lst_order_chp(t_list *chp1, t_list *chp2)
{
	if (!chp1 || !chp2)
		return (-1);
	if (((t_champ*)(chp1->cnt))->id > ((t_champ*)(chp2->cnt))->id)
		return (0);
	return (1);

}

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
	t_list	*chp1;
	t_list	*chp2;
	t_list	*chp3;
	t_list	*chp4;

	tab_champ[0]->next = NULL;
	tab_champ[1]->next = NULL;
	tab_champ[2]->next = NULL;
	tab_champ[3]->next = NULL;
	chp1 = tab_champ[0];
	chp2 = tab_champ[1];
	chp3 = tab_champ[2];
	chp4 = tab_champ[3];
	if (chp1 != NULL)
		new = chp1;
	if (chp2 != NULL)
		ft_lstaddend(&new, chp2);
	if (chp3 != NULL)
		ft_lstaddend(&new, chp3);
	if (chp4 != NULL)
		ft_lstaddend(&new, chp4);
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

int		lst_sort_champion(t_list **champ, int nb_champ)
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
	while (++id <= nb_champ)
	{
		xplr = get_champ_id(champ, id);
		if (xplr != NULL)
			chp[i++] = xplr;
	}
	*champ = reconstruct_champ_list(chp);
	return (1);
}
