/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:33:56 by yaye              #+#    #+#             */
/*   Updated: 2019/04/05 13:33:57 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	unb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		unb = -n;
	}
	else
		unb = n;
	if (unb < 10)
		ft_putchar_fd(unb + '0', fd);
	else
	{
		ft_putnbr_fd(unb / 10, fd);
		ft_putchar_fd(unb % 10 + '0', fd);
	}
}
