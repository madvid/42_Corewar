/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_positive_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:35:39 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/08 18:51:58 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_positive_int(char *str)
{
	int		i;
	unsigned long long	result;

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
		result = 10 * result + ((unsigned long long)str[i] - 48);
		i++;
		if (result > INTEGER_MAX)
			return (-1);
	}
	return (1);
}
