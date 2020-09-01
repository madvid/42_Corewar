/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:10:26 by yaye              #+#    #+#             */
/*   Updated: 2019/04/02 16:10:28 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dsttemp;
	unsigned char	*srctemp;

	i = 0;
	dsttemp = (unsigned char *)dst;
	srctemp = (unsigned char *)src;
	while (i < n)
	{
		dsttemp[i] = srctemp[i];
		if (srctemp[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
