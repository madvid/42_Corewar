/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:18:34 by yaye              #+#    #+#             */
/*   Updated: 2019/02/18 12:18:36 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				is_valid_char(char c)
{
	if (c > 32 && c != '-' && c != '+' && c != 127)
		return (1);
	return (0);
}

int				ft_baselen(char *base)
{
	int		i;
	int		j;

	i = 0;
	while (base[i])
	{
		if (is_valid_char(base[i]) == 0)
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j = j + 1;
		}
		i = i + 1;
	}
	if (i < 2)
		return (0);
	return (i);
}

int				ft_str(char *str, char *base)
{
	int		i;
	int		j;
	int		tof;

	if ((str[0] == '+' && str[1]) || (str[0] == '-' && str[1]) ||
		is_valid_char(str[0]))
	{
		i = 1;
		while (is_valid_char(str[i]))
		{
			j = 0;
			tof = 0;
			while (base[j])
			{
				if (str[i] == base[j])
					tof = 1;
				j = j + 1;
			}
			if (tof == 0)
				return (0);
			i = i + 1;
		}
		return (i);
	}
	return (0);
}

int				ft_atoi_base(char *str, char *base)
{
	int	b;
	int	k;
	int	l;
	int	n;
	int	j;

	if (ft_str(str, base) == 0 || ft_baselen(base) == 0)
		return (0);
	b = ft_baselen(base);
	l = ft_str(str, base);
	n = 0;
	k = 0;
	while (l - 1 - k >= 0 && str[l - 1 - k] != '+' && str[l - 1 - k] != '-')
	{
		j = 0;
		while (str[l - 1 - k] != base[j])
			j++;
		if (str[0] == '-')
			n = n - ft_power(b, k++) * j;
		else
			n = n + ft_power(b, k++) * j;
	}
	return (n);
}
