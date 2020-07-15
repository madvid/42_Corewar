/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:50:58 by yaye              #+#    #+#             */
/*   Updated: 2019/04/02 19:50:59 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_compare(char *str, char *to_fd, size_t len, size_t i)
{
	size_t	j;
	size_t	n;

	j = 0;
	n = 0;
	while (j < len)
	{
		if (str[i] == to_fd[j])
			n = n + 1;
		i = i + 1;
		j = j + 1;
	}
	return (n);
}

char			*ft_strnstr(const char *haystack, const char *needle,
	size_t len)
{
	size_t	i;
	char	*str;
	char	*to_fd;

	str = (char *)haystack;
	to_fd = (char *)needle;
	i = 0;
	while (str[i] != 0 && (i + ft_strlen(needle)) <= len)
	{
		if (ft_compare(str, to_fd, ft_strlen(needle), i) == ft_strlen(needle))
			return (str + i);
		i = i + 1;
	}
	return (0);
}
