/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:09:22 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/14 17:25:01 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function: ft_print_binary
** Description:
**	Prints the binary value of the integer received in parameter.
*/

void	ft_print_binary(int nb)
{
	if (nb)
	{
		ft_print_binary(nb >>= 1);
		ft_putnbr(nb & 1);
	}
}
