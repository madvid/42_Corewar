/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:19:30 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/17 14:34:21 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		ft_error_strrchr(const char *s, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	c = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			count++;
		i++;
	}
	if (count == 0 && c != '\0')
		return (0);
	return (1);
}

char			*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (ft_error_strrchr(s, c) == 0)
		return (0);
	while (i < ft_strlen(s))
	{
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] == c)
		{
			s = s + i;
			i = 1;
		}
	}
	return ((char*)s);
}
