/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:10:59 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 13:10:59 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

static int		ft_sizenb(long long nb)
{
	int count;

	count = 0;
	if (nb == LLONG_MIN)
	{
		count++;
		nb = LLONG_MAX;
	}
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

static char		*ft_makedst2(char *dst, long long nb)
{
	dst[0] = 48;
	dst[1] = '\0';
	return (dst);
}

static char		*ft_makedst(char *dst, long long nb, int i)
{
	if (nb == -0 || nb == 0)
	{
		dst = ft_makedst2(dst, nb);
		return (dst);
	}
	dst[i] = '\0';
	i--;
	if (nb < 0)
	{
		dst[0] = '-';
		if (nb == LLONG_MIN)
		{
			dst[i] = '8';
			nb = nb / 10;
			i--;
		}
		nb = -(long long)nb;
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
	char		*dst;
	long long	nb;

	nb = (long long)nbr;
	if (!(dst = (char*)malloc(sizeof(char) * ft_sizenb(nb))))
		return (NULL);
	dst = ft_makedst(dst, nb, ft_sizenb(nb));
	return (dst);
}
