/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:20:53 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/18 16:57:57 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *cnt, size_t cnt_s)
{
	t_list		*nwlist;

	if (!(nwlist = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (cnt == NULL)
	{
		nwlist->cnt = NULL;
		nwlist->cnt_s = 0;
	}
	else
	{
		if (!(nwlist->cnt = malloc(cnt_s)))
		{
			ft_memdel((void**)&nwlist);
			return (NULL);
		}
		ft_memcpy(nwlist->cnt, cnt, cnt_s);
		nwlist->cnt_s = cnt_s;
	}
	nwlist->next = NULL;
	return (nwlist);
}
