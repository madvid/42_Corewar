/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:24:11 by yaye              #+#    #+#             */
/*   Updated: 2019/04/08 17:24:13 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** RENVOIE LE DERNIER MAILLON DE LA LISTE
**
** RETURN LAST LINK OF THE LIST
*/

t_list		*ft_lstlast(t_list *lst_start)
{
	t_list	*ret;

	if (!lst_start)
		return (NULL);
	ret = lst_start;
	while ((*ret).next)
		ret = (*ret).next;
	return (ret);
}
