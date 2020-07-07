/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbword.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:18:56 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/15 12:13:17 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbword(char const *s, char c)
{
	int		i;
	char	*tmp;
	int		count;

	count = 0;
	tmp = (char*)s;
	i = 0;
	while (tmp[i] == c)
		i++;
	while (tmp[i] != '\0')
	{
		while (tmp[i] != c)
		{
			i++;
		}
		i++;
	}
	return (count);
}
