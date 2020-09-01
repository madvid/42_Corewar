/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:38:36 by yaye              #+#    #+#             */
/*   Updated: 2019/04/02 19:38:37 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	size_t		j;
	int			k;
	char		*ctemp;

	i = 0;
	j = 0;
	k = 0;
	ctemp = (char *)s;
	if (!c)
		return (ctemp + ft_strlen(ctemp));
	while (s[i])
	{
		if (ctemp[i] == (char)c)
		{
			j = i;
			k++;
		}
		i++;
	}
	if (k > 0)
		return (ctemp + j);
	return ((char *)NULL);
}
