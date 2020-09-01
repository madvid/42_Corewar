/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:08:33 by yaye              #+#    #+#             */
/*   Updated: 2019/04/04 19:08:34 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	nwords(char const *str, char c)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (str[i] == c)
		i++;
	while (str[i] && str[i] != c)
	{
		i++;
		if (str[i] == 0 || str[i] == c)
		{
			n++;
			while (str[i] == c)
				i++;
		}
	}
	return (n);
}

static int	nchar(char const *str, int i, char c)
{
	int		n;

	n = 0;
	while (str[i] && str[i] != c)
	{
		n++;
		i++;
	}
	return (n);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	if (!s || (!(str = (char **)malloc(sizeof(char *) * (nwords(s, c) + 1)))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			str[j] = (char *)malloc(sizeof(char) * (nchar(s, i, c) + 1));
			k = 0;
			while (s[i] && s[i] != c)
				str[j][k++] = s[i++];
			str[j++][k] = 0;
		}
		else
			i++;
	}
	str[j] = (char *)0;
	return (str);
}
