/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:20:53 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/28 11:50:23 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *cnt)
{
	t_list		*nwlist;

	if (!(nwlist = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (cnt == NULL)
		nwlist->cnt = NULL;
	else
		nwlist->cnt = (void*)cnt;
	nwlist->next = NULL;
	return (nwlist);
}
