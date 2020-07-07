/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:15:04 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/18 12:35:03 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lenghtdst(char *dst, size_t size)
{
	size_t	i;

	i = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t k;
	size_t l;

	i = ft_strlen(dst);
	k = ft_lenghtdst(dst, size);
	j = 0;
	if (size > i + 1)
		l = size - i - 1;
	else
		return (k + ft_strlen((char*)src));
	while (src[j] != '\0' && j < l)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (k + ft_strlen((char*)src));
}
