/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:12:06 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/15 12:20:33 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;
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
	i = 0;
	while (s[i] != c)
		i++;
	return ((char*)(s + i));
}
