/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:06:52 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/28 13:01:44 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list **alst, void (*del)(void*))
{
	if (!alst || !(*alst))
		return ;
	if ((*alst)->cnt)
	{
		(del)((*alst)->cnt);
		(*alst)->next = NULL;
		free((*alst)->cnt);
	}
	free(*alst);
	*alst = NULL;
}
