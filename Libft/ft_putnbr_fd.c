/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:19:50 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/15 12:19:06 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb >= 0 && nb <= 9)
	{
		ft_putchar_fd((nb + 48), fd);
		return ;
	}
	if (nb > 9 && nb <= 2147483647)
	{
		ft_putnbr_fd((nb / 10), fd);
		ft_putchar_fd((nb % 10 + 48), fd);
	}
	if (nb < 0 && nb > -2147483648)
	{
		ft_putchar_fd(('-'), fd);
		nb = nb * -1;
		ft_putnbr_fd((nb), fd);
	}
	if (nb == -2147483648)
	{
		ft_putchar_fd(('-'), fd);
		nb = 214748364;
		ft_putnbr_fd((nb), fd);
		ft_putchar_fd((8 + 48), fd);
	}
	return ;
}
