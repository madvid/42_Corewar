/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:57:11 by yaye              #+#    #+#             */
/*   Updated: 2019/04/08 11:57:12 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** AJOUTE LE MAILLON *new AU DÉBUT DE LA LISTE
** new DEVIENT LA NOUVELLE TÊTE DE LISTE *alst
**
** ADD *new TO THE LIST FROM THE BEGINNING
** new BECOMES THE NEW *alst
*/

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		(*new).next = (*alst);
		*alst = new;
	}
}
