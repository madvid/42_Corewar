/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:50:57 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/15 12:18:42 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr(int nb)
{
	if (nb >= 0 && nb <= 9)
	{
		ft_putchar(nb + 48);
		return ;
	}
	if (nb > 9 && nb <= 2147483647)
	{
		ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + 48);
	}
	if (nb < 0 && nb > -2147483648)
	{
		ft_putchar('-');
		nb = nb * -1;
		ft_putnbr(nb);
	}
	if (nb == -2147483648)
	{
		ft_putchar('-');
		nb = 214748364;
		ft_putnbr(nb);
		ft_putchar(8 + 48);
	}
	return ;
}
