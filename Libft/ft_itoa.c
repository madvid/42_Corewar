/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:10:59 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/18 15:40:34 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_sizenb(long nb)
{
	int count;

	count = 0;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	if (nb == 0)
		count++;
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static char		*ft_makedst(char *dst, long nb, int i)
{
	if (nb == -0)
	{
		dst[0] = 48;
		dst[1] = '\0';
		return (dst);
	}
	dst[i] = '\0';
	i--;
	if (nb < 0)
	{
		dst[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		dst[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	return (dst);
}

char			*ft_itoa(long long nbr)
{
	char	*dst;
	long	nb;

	nb = (long)nbr;
	if (!(dst = (char*)malloc(sizeof(char) * ft_sizenb(nb) + 1)))
		return (NULL);
	dst = ft_makedst(dst, nb, ft_sizenb(nb));
	return (dst);
}
