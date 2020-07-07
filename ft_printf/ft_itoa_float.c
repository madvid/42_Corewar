/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:57:42 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/16 13:36:30 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_float_sign(float nb, t_print *p, int i, int sign)
{
	int				j;
	int				k;
	char			integer[9];
	char			deci[25];
	union u_decimal	fu;

	fu.f = nb;
	i = sizeof(nb) * CHAR_BIT;
	j = 0;
	k = 0;
	while (i--)
	{
		if (i == 31)
			sign = (fu.u >> i) & 0x1;
		else if (i < 31 && i >= 23)
			integer[j++] = ((fu.u >> i) & 0x1) + '0';
		else
			deci[k++] = ((fu.u >> i) & 0x1) + '0';
	}
	return (sign);
}

char	*ft_itoa_float2(t_print *p, char *s, char *tmp)
{
	while (p->ipart != 0)
	{
		tmp = ft_itoa(p->ipart);
		s = ft_strcat(s, tmp);
		free(tmp);
		p->fpart = p->ipart - (float)p->fpart;
		p->fpart *= 10;
		p->ipart = (int)p->fpart;
		p->ipart = (p->ipart < 0) ? -p->ipart : p->ipart;
		p->fpart = (p->fpart < 0) ? -p->fpart : p->fpart;
		p->len++;
	}
	p->len = (p->len > p->precision) ? p->precision : p->len;
	return (s);
}

char	*ft_itoa_float(double nb, t_print *p, int sign)
{
	char	*s;
	char	*tmp;

	p->len = 0;
	p->ipart = (int)nb;
	p->fpart = nb - (float)p->ipart;
	p->ipart = (p->ipart < 0) ? -p->ipart : p->ipart;
	p->fpart = (p->fpart < 0) ? -p->fpart : p->fpart;
	s = ft_strnew(-1);
	s[0] = '\0';
	tmp = ft_itoa(p->ipart);
	if (sign == 1)
		s = ft_strjoin("-", tmp);
	else
		s = ft_strjoin(s, tmp);
	free(tmp);
	s = ft_strcat(s, ".");
	p->fpart *= 10;
	p->ipart = (int)p->fpart;
	s = ft_itoa_float2(p, s, tmp);
	tmp = s;
	free(s);
	s = tmp;
	return (s);
}

int		ft_floatlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '.')
		i++;
	i++;
	return (i);
}
