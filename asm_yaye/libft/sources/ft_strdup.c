/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:52:34 by yaye              #+#    #+#             */
/*   Updated: 2019/04/02 18:52:36 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;

	if (!(dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return ((char *)NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
