/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:19:49 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/05 10:13:42 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

static int		ft_sizenb(unsigned long long nb)
{
	int count;

	count = 0;
	if (nb == 0)
		count++;
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static char		*ft_makedst2(char *dst, unsigned long long nb)
{
	dst[0] = 48;
	dst[1] = '\0';
	return (dst);
}

static char		*ft_makedst(char *dst, unsigned long long nb, int i)
{
	if (nb == -0)
	{
		dst = ft_makedst2(dst, nb);
		return (dst);
	}
	dst[i] = '\0';
	i--;
	while (nb > 0)
	{
		dst[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	return (dst);
}

char			*ft_unsigned_itoa(unsigned long long nbr)
{
	char				*dst;
	unsigned long long	nb;

	nb = (unsigned long long)nbr;
	if (!(dst = (char*)malloc(sizeof(char) * ft_sizenb(nb) + 1)))
		return (NULL);
	dst = ft_makedst(dst, nb, ft_sizenb(nb));
	return (dst);
}
