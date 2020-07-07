/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:05:43 by armajchr          #+#    #+#             */
/*   Updated: 2019/11/18 14:05:18 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (0);
	k = ft_strnbword(s, c);
	i = 0;
	j = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * k + 1)))
		return (NULL);
	while (i < k)
	{
		while (s[j] == c && s[j] != '\0')
			j++;
		tab[i] = ft_get_word(s, c);
		s = (char*)s + j + ft_strlen(tab[i]);
		i++;
		j = 0;
	}
	tab[i] = NULL;
	return (tab);
}
