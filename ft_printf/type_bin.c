/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:26:40 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 12:38:16 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base(long long nb, char *base)
{
	int				count;
	long long		tmp;
	char			*res;
	unsigned int	base_lenght;

	base_lenght = ft_strlen(base);
	count = (nb < 0) ? 2 : 1;
	tmp = (nb < 0) ? -nb : nb;
	while (tmp >= base_lenght && (tmp /= base_lenght))
		count++;
	tmp = (nb < 0) ? -nb : nb;
	if (!(res = (char*)malloc(sizeof(char) * count)))
		return (NULL);
	if (nb < 0)
		res[0] = '-';
	res[count] = '\0';
	while (tmp >= base_lenght)
	{
		count--;
		res[count] = base[tmp % base_lenght];
		tmp /= base_lenght;
	}
	count--;
	res[count] = base[tmp % base_lenght];
	return (res);
}

char	*type_bin_option(t_print *p, int nb, char *s)
{
	if (nb < 0)
	{
		s = s + 1;
		fill_buffer('-', p);
		fill_buffer('0', p);
		fill_buffer('b', p);
	}
	return (s);
}

void	type_bin_precision(t_print *p, char *s, int nb)
{
	if (p->len >= p->precision && nb != 0)
	{
		type_hexa_basic_fill(p, s);
		return ;
	}
	if (p->len < p->precision || p->precision == 1)
	{
		(nb == 0 && p->precision > 1 && p->widht >= 0) ? p->len-- : 0;
		while (p->len < p->precision && p->f & (F_POINT) && p->precision != 1)
		{
			fill_buffer('0', p);
			p->len++;
		}
		(nb == 0 && p->f & (F_POINT) && p->widht > 0 && p->precision == 1)
			? fill_buffer(' ', p) : 0;
		if (nb != 0 || ((nb == 0) && !(p->f & (F_POINT))))
			type_hexa_basic_fill(p, s);
		return ;
	}
	else
		fill_buffer(' ', p);
}

void	type_bin_widht(t_print *p, char *s, int nb)
{
	if (p->len > p->widht && p->precision == 1 && nb != 0)
	{
		s = type_bin_option(p, nb, s);
		type_hexa_basic_fill(p, s);
		return ;
	}
	if (p->widht <= p->precision)
	{
		s = type_bin_option(p, nb, s);
		type_bin_precision(p, s, nb);
	}
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& !(p->f & (F_MINUS)))
		type_bin_spe_fill(p, s, nb);
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& p->f & (F_MINUS))
	{
		s = type_bin_option(p, nb, s);
		type_bin_precision(p, s, nb);
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
	}
}

void	type_bin(t_print *p)
{
	int		nb;
	char	*s;
	char	*tmp;

	nb = va_arg(p->ap, int);
	s = ft_itoa_base(nb, "01");
	tmp = s;
	free(s);
	s = tmp;
	p->len = ft_strlen(s);
	if (p->len >= p->widht && !(p->f & (F_POINT)))
	{
		s = type_bin_option(p, nb, s);
		type_hexa_basic_fill(p, s);
		return ;
	}
	else
		type_bin_mod(p, nb);
	if (p->widht == 0 && p->precision == 1)
	{
		s = type_bin_option(p, nb, s);
		type_hexa_basic_fill(p, s);
		return ;
	}
	type_bin_widht(p, s, nb);
}
