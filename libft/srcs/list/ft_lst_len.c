/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:47:52 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/10 11:58:03 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function: ft_lst_len
** Description:
**	Counts the number of link within the list.
** Return:
**	len: number of link
**	0: if lst is NULL
** -1: if the length is bigger than an int
*/

int		ft_lst_len(t_list *lst)
{
	size_t		len;
	t_list		*xplr;

	len = 0;
	if (lst == NULL)
		return (0);
	xplr = lst;
	while (xplr)
	{
		len++;
		if (len > INTEGER_MAX)
			return (-1);
		xplr = xplr->next;
	}
	return (len);
}
