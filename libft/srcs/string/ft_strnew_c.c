/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 11:06:46 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/04 11:13:54 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** Function: ft_strnew_c
** Description:
**	Modified version of ft_strnew.
**	Function allocates a string of length 'size+1' (last byte is NULL-byte)
**	and inializes each character of the string to the value 'c'.
** Return:
**	s:
**	NULL: otherwise
*/

char		*ft_strnew_c(size_t size, char c)
{
	char	*s;
	size_t	i;

	if (!(s = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	s[size] = '\0';
	i = 0;
	while (i < size)
	{
		s[i] = c;
		i++;
	}
	return (s);
}
