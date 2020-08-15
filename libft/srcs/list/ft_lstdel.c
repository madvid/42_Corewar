/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:35:16 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/14 15:57:05 by armajchr         ###   ########.fr       */
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
		del(before->cnt, before->cnt_s);
		ft_memdel((void**)&before);
		before = NULL;
	}
	*alst = NULL;
}
