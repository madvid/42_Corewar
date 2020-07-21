/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:02:48 by weilin            #+#    #+#             */
/*   Updated: 2018/11/23 15:24:05 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char			*s;
	int				len;
	int				sign;
	unsigned int	nb;

	sign = (n < 0) ? -1 : 1;
	len = ft_int_len(n);
	nb = sign * n;
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = '\0';
	if (nb == 0)
		s[0] = '0';
	while (nb)
	{
		s[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	if (sign == -1)
		s[0] = '-';
	return (s);
}
