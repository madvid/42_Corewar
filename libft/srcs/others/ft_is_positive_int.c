/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_positive_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:35:39 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/10 20:38:38 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function: ft_is_positive_int
** Description:
**	Function checks if the string received as parameter corresponds to positive
**	integer.
** Return:
**	1: if the string parameter is a positive integer
**	0: if the parameter string is not a positive integer
*/

int		ft_is_positive_int(char *str)
{
	int		i;
	size_t	result;

	i = 0;
	result = 0;
	if (!str || (str && !str[0]))
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (0);
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		result = 10 * result + ((size_t)str[i] - 48);
		i++;
		if (result > INTEGER_MAX)
			return (0);
	}
	return (1);
}
