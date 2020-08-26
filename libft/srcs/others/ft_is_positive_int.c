/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_positive_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:35:39 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/21 13:27:44 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function: ft_is_positive_int
** Description:
**	Function checks if the string received as parameter corresponds to positive
**	integer (zero included).
** Return:
**	1: if the string parameter is a positive integer or zero
**	-1: if the parameter string is not a positive integer
*/

int		ft_is_positive_int(char *str)
{
	int		i;
	size_t	result;

	i = 0;
	result = 0;
	if (!str || (str && !str[0]))
		return (-1);
	if (str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		result = 10 * result + ((size_t)str[i] - 48);
		i++;
		if (result > INTEGER_MAX)
			return (-1);
	}
	return (str[i] == '\0' ? (int)result : -1);
}
