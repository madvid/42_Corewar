/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:45:46 by yaye              #+#    #+#             */
/*   Updated: 2019/04/02 17:45:48 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ctemp;

	i = 0;
	ctemp = (unsigned char *)s;
	while (i < n)
	{
		if (ctemp[i] == (unsigned char)c)
			return (ctemp + i);
		i++;
	}
	return ((void *)NULL);
}
