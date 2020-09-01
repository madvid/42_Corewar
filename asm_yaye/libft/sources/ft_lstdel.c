/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:39:34 by yaye              #+#    #+#             */
/*   Updated: 2019/04/08 10:39:36 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** FREE TOUTE LA LISTE À PARTIR DE LA TÊTE DE LISTE alst
** *alst POINTE SUR NULL
**
** FREE THE ENTIRE LIST FROM alst
** *alst SET TO NULL
*/

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*tmp;
	t_list		*bis;

	if (!(*alst))
		return ;
	bis = *alst;
	while (bis)
	{
		tmp = bis;
		bis = (*tmp).next;
		del((*tmp).content, (*tmp).content_size);
		free(tmp);
	}
	*alst = NULL;
}
