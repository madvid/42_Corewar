/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_to_dc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 14:55:59 by yaye              #+#    #+#             */
/*   Updated: 2020/07/09 14:56:00 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t		ft_power(size_t x, int power)
{
	if (power > 0)
	{
		if (x >= 9223372036854775807 / ft_power(x, power - 1))
			return (0);
		return (x * ft_power(x, power - 1));
	}
	if (power < 0)
		return (0);
	return (1);
}

size_t		ft_bi_to_dc(char *bi)
{
	size_t	dec;
	size_t	len;
	int		power;

	dec = 0;
	len = -1;
	power = 0;
	while (bi[++len])
		if (bi[len] != '0' && bi[len] != '1')
			return (0);
	if (!len)
		return (0);
	while (++power <= len)
		dec = dec + (bi[len - power] - '0') * ft_power(2, power - 1);
	return (dec);
}
