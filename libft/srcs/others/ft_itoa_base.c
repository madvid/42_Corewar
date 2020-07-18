/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 12:07:44 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/14 23:10:27 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function: ft_nbrlen
** Description:
**	Calculate the number of digits of a unsigned int number.
** Return:
**	len: length in term of digit of the unsigned number parameter
*/

static int				ft_nbrlen_base(unsigned int nb, int base)
{
	int		len;

	len = 1;
	while ((nb = nb / base) > 0)
		len++;
	return (len);
}

/*
** Function: ft_abs
** Description:
**	Calculate the absolute value of the integer number parameter.
** Return:
**	abs_val : absolute value of the integer parameter.
** Reminder:
**	INT_MIN = -2147483648
**	INT_MAX = 2147483647
*/

static unsigned int		ft_abs(int nb)
{
	int		sign;

	sign = 1;
	if (nb < 0)
		sign = -1;
	return ((unsigned int)(sign * nb));
}

/*
** Function: ft_itoa_base
** Description:
**	Converts the parameter nb into the base specified in parameter, using
**	the character table received in parameter (char *strbase).
** Return:
**	str: nb integer converted in the specified base and casting in string.
**	NULL: if memory allocation issue or if nb < 0 and the base != 10.
*/

char					*ft_itoa_base(int nb, char *strbase, int base)
{
	unsigned int	u_nb;
	int				len;
	char			*str;

	u_nb = ft_abs(nb);
	len = ft_nbrlen_base(u_nb, base);
	str = (nb < 0 && base == 10) ? ft_strnew(++len) : ft_strnew(len);
	if ((nb < 0 && base != 10) || !str)
	{
		ft_strdel(&str);
		return (NULL);
	}
	while (len > 0)
	{
		str[len - 1] = strbase[u_nb % base];
		u_nb = (u_nb - u_nb % base) / base;
		len--;
	}
	if (nb < 0 && base == 10)
		str[0] = '-';
	return (str);
}
