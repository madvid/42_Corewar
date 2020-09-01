/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:34:27 by yaye              #+#    #+#             */
/*   Updated: 2019/04/02 15:34:29 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** REINITIE LES VALEURS à 0 DANS s
** PORTÉE = (*s) à (*s) + (n - 1)
**
** SET TO 0
** RANGE = (*s) to (*s) + (n - 1)
*/

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)s;
	while (i < n)
	{
		temp[i] = (unsigned char)0;
		i++;
	}
}
