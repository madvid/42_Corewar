/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_champion_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:02:30 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/10 18:23:42 by mdavid           ###   ########.fr       */
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
**
**
**
**
*/

t_list	*lst_bubble(t_list *link1, t_list *link2)
{
	t_list		*head;

	head = link1;
	while(head != NULL && ft_lst_issort(head, &lst_order_chp) == 0)
	{
		ft_printf("link1 = %p -- link2 = %p\n", link1, link2);
		ft_printf("valeur de lst_order_chp(l1, l2) = %d\n", lst_order_chp(link1, link2));
		tool_print_short_champ_list(head);
		ft_printf("\n");
		if (lst_order_chp(link1, link2) == 1)
		{
			ft_printf("1er if\n");
			head = lst_bubble(link1->next, link2->next);
		}
		if (lst_order_chp(link1, link2) == 0)
		{
			ft_printf("2nd if\n");
			head = ft_lst_swap(link1, link2);
		}
		ft_printf("after\n");
	}
	return (head);
}

/*
** Function: sort_champion
** Description:
**	
** Return:
**	1: the list has been sorted
**	0: if the list to sort is NULL
*/

int		lst_sort_champion(t_list **champ)
{
	t_list	*xplr1;
	t_list	*xplr2;

	/*if (ft_lst_len(*champ) == -1)
		return (0);
	if (ft_lst_len(*champ) == 1)
		return (1);*/
	xplr1 = *champ;
	xplr2 = (*champ)->next;
	/*if (ft_lst_len(*champ) == 2
		&& ((t_champ*)(xplr1->cnt))->id > ((t_champ*)(xplr2->cnt))->id)
	{
		ft_printf(">>>>>>>>>>>>>>> ici n champ = 2 <<<<<<<<<<<<<<<<<\n");
		tool_print_champ_list(*champ);
		*champ = ft_lst_swap(xplr1, xplr2);
		tool_print_champ_list(*champ);
		ft_printf(">>>>>>>>>>>>>>>>>>>>> fin <<<<<<<<<<<<<<<<<<<<<<<\n");
		return (1);
	}*/
	ft_printf(">>>>>>>>>>>>>>> ici n champ = 3/4 <<<<<<<<<<<<<<<<<\n");
	tool_print_short_champ_list(*champ);
	ft_printf(">>>>>>>>>>>>>>>>> middle <<<<<<<<<<<<<<<<<<<\n");
	*champ = lst_bubble(xplr1, xplr2);
	ft_printf(">>>>>>>>>>>>>>>>> middle fin<<<<<<<<<<<<<<<<<<<\n");
	tool_print_short_champ_list(*champ);
	ft_printf(">>>>>>>>>>>>>>>>>>>>> fin <<<<<<<<<<<<<<<<<<<<<<<\n");
	return (1);
}