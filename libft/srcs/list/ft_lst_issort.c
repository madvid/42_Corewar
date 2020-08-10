/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_issort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 12:00:27 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/10 18:24:39 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function: ft_lst_issort
** Description:
**	Checks if the list given as parameter is sorted according to the function
**	of ordering.
** Return:
**	1: list is sorted.
**	0: list not sorted.
**	-1: list is actually NULL
*/

int		ft_lst_issort(t_list *lst, int (*ft_lst_order)(t_list*, t_list*))
{
	t_list		*xplr1;
	t_list		*xplr2;

	if (lst == NULL)
		return (-1);
	if (ft_lst_len(lst) == 1)
		return (1);
	xplr1 = lst;
	xplr2 = lst->next;
	while (xplr1 && xplr2)
	{
		ft_putstr("toto\n");
		if (ft_lst_order(xplr1, xplr2) == 0)
			return (0);
		xplr1 = xplr1->next;
		xplr2 = xplr2->next;
	}
	return (1);
}