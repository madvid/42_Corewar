/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:42:52 by yaye              #+#    #+#             */
/*   Updated: 2019/04/02 19:42:53 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_compare(char *str, char *to_find, size_t len, size_t i)
{
	size_t	j;
	size_t	n;

	j = 0;
	n = 0;
	while (j < len)
	{
		if (str[i] == to_find[j])
			n = n + 1;
		i = i + 1;
		j = j + 1;
	}
	return (n);
}

char			*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	len;
	char	*str;
	char	*to_find;

	if (!haystack)
		return (0);
	str = (char *)haystack;
	to_find = (char *)needle;
	i = 0;
	len = 0;
	if (needle[0] == 0)
		return (str);
	while (to_find[len] != 0)
		len = len + 1;
	while (str[i] != 0)
	{
		if (ft_compare(str, to_find, len, i) == len)
			return (str + i);
		i = i + 1;
	}
	return (0);
}
