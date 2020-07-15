/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddbel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:59:14 by yaye              #+#    #+#             */
/*   Updated: 2019/06/18 13:01:31 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** AJOUTE LE MAILLON *new EN FIN DE LISTE
**
** ADD *new TO THE END OF THE LIST
*/

void		ft_lstaddbel(t_list **alst, t_list *new)
{
	t_list	*lpt;

	if (!alst || new)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		lpt = *alst;
		while (lpt->next)
			lpt = lpt->next;
		lpt->next = new;
	}
}
