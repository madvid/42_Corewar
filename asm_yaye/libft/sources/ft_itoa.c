/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:26:09 by yaye              #+#    #+#             */
/*   Updated: 2019/04/04 19:26:10 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_nlen(int n, size_t *len)
{
	if ((n / 10) == 0)
		*len = *len + 1;
	else
	{
		*len = *len + 1;
		ft_nlen(n / 10, len);
	}
}

static void	ft_rec(int n, char *itoa, size_t index, int sign)
{
	if (!itoa)
		return ;
	if ((n / 10) == 0)
		itoa[index] = n * sign + '0';
	else
	{
		itoa[index] = (n % 10) * sign + '0';
		ft_rec(n / 10, itoa, index - 1, sign);
	}
}

char		*ft_itoa(int n)
{
	char	*itoa;
	int		sign;
	size_t	len;

	len = 0;
	sign = 1;
	if (n < 0)
	{
		len++;
		sign = -1;
	}
	ft_nlen(n, &len);
	if (!(itoa = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	itoa[len--] = 0;
	if (n < 0)
		itoa[0] = '-';
	ft_rec(n, itoa, len, sign);
	return (itoa);
}
