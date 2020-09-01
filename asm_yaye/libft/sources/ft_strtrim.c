/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:58:15 by yaye              #+#    #+#             */
/*   Updated: 2019/04/04 18:58:16 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_empty(void)
{
	char	*s;

	if (!(s = (char *)malloc(sizeof(char))))
		return (NULL);
	s[0] = 0;
	return (s);
}

char		*ft_strtrim(char const *s)
{
	unsigned int	start;
	size_t			len;
	size_t			end;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] && (s[start] == ' ' || s[start] == '\n' ||
		s[start] == '\t'))
		start++;
	len = 0;
	while (s[start + len])
	{
		end = start + len;
		while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		{
			end++;
			if (!s[end])
				return (ft_strsub(s, start, len));
		}
		len++;
	}
	if (!len || !(*s))
		return (ft_empty());
	return (ft_strsub(s, start, len));
}
