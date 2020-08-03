/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:15:46 by weilin            #+#    #+#             */
/*   Updated: 2020/02/24 15:48:45 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_ulltoa(unsigned long long n)
{
	char					*val;
	int						len;
	unsigned long long int	tmp;

	len = 1;
	tmp = n;
	while (tmp >= 10)
	{
		tmp /= 10;
		len++;
	}
	if (!(val = ft_memalloc(len + 1)))
		return (NULL);
	val[len] = '\0';
	tmp = n;
	while (tmp >= 10)
	{
		val[--len] = (tmp % 10) + '0';
		tmp /= 10;
	}
	val[--len] = (tmp % 10) + '0';
	return (val);
}

/*
** FONCTION: ft_uitoa.
** PARAMETERS: unsigned int n: an unsigned int number.
** DESCRIPTION:
** 	Convert an unsigned integer to a string.
** RETURN:
** 	NULL: if an allocation memory problem comes up.
** 	char *val
*/

char	*ft_uitoa(unsigned int n)
{
	char			*val;
	int				len;
	unsigned int	tmp;

	len = 1;
	tmp = n;
	while (tmp >= 10)
	{
		tmp /= 10;
		len++;
	}
	if (!(val = ft_memalloc(len + 1)))
		return (NULL);
	val[len] = '\0';
	tmp = n;
	while (tmp >= 10)
	{
		val[--len] = (tmp % 10) + '0';
		tmp /= 10;
	}
	val[--len] = (tmp % 10) + '0';
	return (val);
}

char	*ft_ulltoa_base(unsigned long long n, unsigned long long base)
{
	char					*val;
	int						len;
	unsigned long long		tmp;

	len = 1;
	tmp = n;
	while (tmp >= base)
	{
		tmp /= base;
		len++;
	}
	if (!(val = ft_memalloc(len + 1)))
		return (NULL);
	val[len] = '\0';
	tmp = n;
	while (tmp >= base)
	{
		val[--len] = (tmp % base) > 9 ?
			(tmp % base) + 55 : (tmp % base) + '0';
		tmp /= base;
	}
	val[--len] = (tmp % base) > 9 ?
		(tmp % base) + 55 : (tmp % base) + '0';
	return (val);
}

/*
** FONCTION: ft_ultoa_base.
** PARAMETERS: unsigned long int n: an unsigned long int number.
** DESCRIPTION:
** 	Convert an unsigned long integer to a string in uppercase on assigned base
** 	to have lowercase string, change the number 55 to 87
** RETURN:
** 	NULL: if an allocation memory problem comes up.
** 	char *s
*/

char	*ft_ultoa_base(unsigned long n, unsigned long base)
{
	char				*s;
	int					len;
	unsigned long		tmp;

	len = 1;
	tmp = n;
	while (tmp >= base)
	{
		tmp /= base;
		len++;
	}
	if (!(s = ft_strnew(len)))
		return (NULL);
	s[len] = '\0';
	tmp = n;
	while (tmp >= base)
	{
		s[--len] = (tmp % base) > 9 ?
			(tmp % base) + 55 : (tmp % base) + '0';
		tmp /= base;
	}
	s[--len] = (tmp % base) > 9 ?
		(tmp % base) + 55 : (tmp % base) + '0';
	return (s);
}

char	*ft_uitoa_base(unsigned int n, unsigned int base)
{
	char			*val;
	int				len;
	unsigned int	tmp;

	len = 1;
	tmp = n;
	while (tmp >= base)
	{
		tmp /= base;
		len++;
	}
	if (!(val = ft_strnew(len)))
		return (NULL);
	val[len] = '\0';
	tmp = n;
	while (tmp >= base)
	{
		val[--len] = (tmp % base) > 9 ?
			(tmp % base) + 55 : (tmp % base) + '0';
		tmp /= base;
	}
	val[--len] = (tmp % base) > 9 ?
		(tmp % base) + 55 : (tmp % base) + '0';
	return (val);
}
