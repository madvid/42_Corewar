/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:07:23 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/17 14:29:28 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*str;
	char	*dest;

	str = (char*)s1;
	dest = (char*)s2;
	i = 0;
	while (i < n)
	{
		if (str[i] != dest[i])
			return ((unsigned char)str[i] - (unsigned char)dest[i]);
		i++;
	}
	return (0);
}
