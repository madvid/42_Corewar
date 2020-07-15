/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:05:26 by yaye              #+#    #+#             */
/*   Updated: 2019/04/08 12:05:27 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** APPLIQUE LA FONCTION f À CHAQUE MAILLON À PARTIR DE lst
**
** APLLY f TO elem IN EACH LINK FROM lst
*/

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	while (lst)
	{
		f(lst);
		lst = (*lst).next;
	}
}
