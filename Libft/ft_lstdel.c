/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:12:40 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/17 14:59:11 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *before;

	tmp = *alst;
	while (tmp)
	{
		before = tmp;
		tmp = tmp->next;
		del(before->content, before->content_size);
		free(before);
		before = NULL;
	}
	*alst = NULL;
}
