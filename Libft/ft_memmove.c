/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:08:55 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/17 15:43:19 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = (unsigned char*)dst;
	i = 0;
	if (tmp > (unsigned char*)src)
	{
		while (i < len)
		{
			tmp[len - 1] = ((unsigned char*)src)[len - 1];
			len--;
		}
		return (dst);
	}
	while (i < len)
	{
		tmp[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (dst);
}
