/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:34:19 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 13:41:20 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int		ft_strjoinlen(char const *s1)
{
	int k;

	if (!s1)
		k = 0;
	else
		k = ft_strlen(s1);
	return (k);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	j = 0;
	k = ft_strjoinlen(s1);
	if (!(str = (char*)malloc(sizeof(char) * (k + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i] && k > 0)
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
