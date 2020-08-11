/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:35:16 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/11 15:01:59 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (!alst || !(*alst))
		return ;
	if ((*alst)->next)
	{
		ft_lstdel(&((*alst)->next), del);
		(*alst)->next = NULL;
	}
	del(*alst, (*alst)->cnt_s);
}
