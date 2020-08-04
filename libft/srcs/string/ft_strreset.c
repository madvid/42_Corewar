/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 10:56:49 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/04 11:02:34 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function: ft_strreset
** Description:
**	Function free the 1st string and make  s1 pointing onto the 2nd string s2.
**	A control is present checking if either s1 or s2 is NULL.
*/

char	*ft_strreset(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (NULL);
	ft_strdel(&s1);
	s1 = s2;
	return (s1);
}
