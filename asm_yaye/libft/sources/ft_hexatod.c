/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexatod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:49:49 by yaye              #+#    #+#             */
/*   Updated: 2019/06/23 13:49:51 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** BASE HEXADECIMALE = 0123456789ABCDEF
*/

int		ft_ishexa(char *str)
{
	if (!str)
		return (0);
	if (!(*str))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) || ((*str) > 'F' && (*str) <= 'Z') \
			|| ((*str) > 'f' && (*str) <= 'z'))
			return (0);
		str = str + 1;
	}
	return (1);
}

char	*hexabase(void)
{
	return ("0123456789abcdef");
}

int		ft_hexatod(char *str)
{
	char	*base;
	int		tod;
	int		i;
	int		j;
	int		k;

	if (!ft_ishexa(str))
		return (0);
	base = hexabase();
	tod = 0;
	i = -1;
	k = ft_strlen(str) - 1;
	while (str[++i])
	{
		j = 0;
		while ((base[j] != (str[i])))
			j++;
		tod = tod + (j * ft_power(16, k--));
	}
	return (tod);
}
