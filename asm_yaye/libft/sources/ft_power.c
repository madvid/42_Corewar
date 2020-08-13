/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 11:38:47 by yaye              #+#    #+#             */
/*   Updated: 2019/05/10 11:38:48 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t		ft_power(size_t x, int power)
{
	size_t		y;

	y = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 0)
	{
		if (x >= 9223372036854775807 / y)
			return (0);
		y *= x;
		power -= 1;
	}
	return (y);
}