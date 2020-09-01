/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:43:14 by yaye              #+#    #+#             */
/*   Updated: 2019/04/05 11:43:16 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	unb;

	if (n < 0)
	{
		ft_putchar('-');
		unb = -n;
	}
	else
		unb = n;
	if (unb < 10)
		ft_putchar(unb + '0');
	else
	{
		ft_putnbr(unb / 10);
		ft_putchar(unb % 10 + '0');
	}
}
