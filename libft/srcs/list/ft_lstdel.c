/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:35:16 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/28 13:01:26 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *))
{
	if ((*alst)->next)
	{
		ft_lstdel(&((*alst)->next), del);
		(*alst)->next = NULL;
	}
	if ((*alst)->cnt)
	{
		del((*alst)->cnt);
		(*alst)->next = NULL;
		free((*alst)->cnt);

	}
	free(*alst);
	*alst = NULL;
}
