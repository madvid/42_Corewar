/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:41:25 by yaye              #+#    #+#             */
/*   Updated: 2019/04/02 15:41:27 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
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
		i++;
	}
	return (dst);
}
