/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 10:21:43 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/11 12:06:24 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function: ft_lstaddend
** Description:
**	Add the link 'add' at the end of the list alst if the list exists and the
**	link as well.
*/

void	ft_lstaddend(t_list **alst, t_list *add)
{
	t_list	*xplr;

	if (!alst || !*alst || !add)
		return ;
	xplr = *alst;
	while (xplr->next)
		xplr = xplr->next;
	xplr->next = add;
}
