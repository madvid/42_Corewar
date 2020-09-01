/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:41:19 by yaye              #+#    #+#             */
/*   Updated: 2019/04/04 17:41:20 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** CRÉE UNE CHAINE MALLOQUÉE DE LONGUEUR size ET RAJOUTE UN 0 FINAL
**
** CREATE A NEW STRING OF size LENGHT AND TERMINATE IT WITH A 0
*/

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str = (char *)ft_memset(str, 0, size + 1);
	return (str);
}
