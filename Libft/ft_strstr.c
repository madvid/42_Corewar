/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:20:07 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/15 12:25:46 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = (char*)str;
	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (tmp);
	if (tmp[i] == '\0')
		return (0);
	while (tmp[i] != '\0')
	{
		while (to_find[j] == tmp[i + j])
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
