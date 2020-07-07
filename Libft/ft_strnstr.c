/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:18:49 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/15 12:24:03 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	tmp = (char*)str;
	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (tmp);
	if (tmp[i] == '\0' || len < ft_strlen(to_find))
		return (0);
	while (tmp[i] != '\0' && i < len)
	{
		while (to_find[j] == tmp[i + j] && (i + j) < len)
		{
			if (to_find[j + 1] == '\0')
				return (tmp + i);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}
