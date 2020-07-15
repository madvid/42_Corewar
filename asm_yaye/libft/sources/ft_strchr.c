/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:34:16 by yaye              #+#    #+#             */
/*   Updated: 2019/04/02 19:34:18 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ctemp;

	i = 0;
	ctemp = (char *)s;
	if (!c)
		return (ctemp + ft_strlen(ctemp));
	while (ctemp[i])
	{
		if (ctemp[i] == (char)c)
			return (ctemp + i);
		i++;
	}
	return (NULL);
}
