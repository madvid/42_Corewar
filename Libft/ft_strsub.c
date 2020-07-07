/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:22:22 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/17 14:34:49 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	d;

	if (!s)
		return (0);
	d = (size_t)start;
	i = 0;
	if (d > ft_strlen(s))
		return (NULL);
	if (d + len > ft_strlen(s))
		return (NULL);
	if (!(dst = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		dst[i] = s[d];
		d++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
