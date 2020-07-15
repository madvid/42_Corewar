/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:29:40 by yaye              #+#    #+#             */
/*   Updated: 2019/04/08 17:29:41 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** RENVOIE LE PREMIER MAILLON CONTENANT needle DANS void *content
**
** RETURN THE FIRST LINK THAT CONTAINS needle IN void *content
*/

t_list	*ft_lstlst(t_list *lst_start, void *needle)
{
	t_list	*lst;

	if (!lst_start)
		return (NULL);
	lst = lst_start;
	while ((*lst).next && !ft_strequ((*lst).content, needle))
		lst = lst->next;
	if (ft_strequ((*lst).content, needle))
		return (lst);
	return (NULL);
}
