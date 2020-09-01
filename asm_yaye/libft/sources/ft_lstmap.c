/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:10:37 by yaye              #+#    #+#             */
/*   Updated: 2019/04/08 12:10:38 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*new;

	if (!lst)
		return (NULL);
	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	tmp = f(lst);
	new = tmp;
	while ((*lst).next)
	{
		(*tmp).next = f((*lst).next);
		tmp = (*tmp).next;
		lst = (*lst).next;
	}
	(*tmp).next = NULL;
	return (new);
}
