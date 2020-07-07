/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:41:19 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/12 11:09:23 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;

	if (!lst)
		return (NULL);
	if (!(tmp = ft_lstnew(f(lst)->content, f(lst)->content_size)))
		return (NULL);
	tmp->next = ft_lstmap(lst->next, f);
	return (tmp);
}
