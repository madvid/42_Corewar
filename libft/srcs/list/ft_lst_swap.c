/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 13:33:50 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/10 15:19:35 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function: ft_lst_swap
** Description:
**	Swaps the 2 links given as arguments. The 2 links have to be consecutive
**	within the list.
** Return:
**	link2
**	NULL: if one of the two links is NULL
*/

t_list		*ft_lst_swap(t_list * link1, t_list *link2)
{
	if (link1 && link2)
	{
		link1->next = link2->next;
		link2->next = link1;
		return (link2);
	}
	return (NULL);
}
