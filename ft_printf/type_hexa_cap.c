/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_hexa_cap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 16:06:13 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 12:49:04 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_hexa_cap_option(t_print *p, long long nb)
{
	if (nb != 0)
	{
		if (p->f & (F_SHARP))
		{
			fill_buffer('0', p);
			fill_buffer('X', p);
		}
	}
}

void	type_hexa_cap_precision(t_print *p, char *s, long long nb)
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
		(nb == 0 && p->f & (F_POINT) && p->widht > 0 && p->precision == 1) ?
			fill_buffer(' ', p) : 0;
		if (nb != 0 || ((nb == 0) && !(p->f & (F_POINT))))
			type_hexa_basic_fill(p, s);
		return ;
	}
	else
		fill_buffer(' ', p);
}

void	type_hexa_cap_widht(t_print *p, char *s, long long nb)
{
	if (p->len > p->widht && p->precision == 1 && nb != 0)
	{
		type_hexa_cap_option(p, nb);
		type_hexa_basic_fill(p, s);
		return ;
	}
	if (p->widht <= p->precision)
	{
		type_hexa_cap_option(p, nb);
		type_hexa_cap_precision(p, s, nb);
	}
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& !(p->f & (F_MINUS)))
		type_hexa_special_fill(p, s, nb);
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& p->f & (F_MINUS))
		type_hexa_cap_spefill2(p, s, nb);
	else
	{
		type_hexa_cap_option(p, nb);
		type_hexa_cap_precision(p, s, nb);
	}
}

void	type_hexa_cap(t_print *p)
{
	long long	nb;
	char		*s;
	char		*tmp;

	nb = type_hexa_cap_size(p, nb);
	s = ft_itoa_base2(nb, "0123456789ABCDEF");
	tmp = s;
	free(s);
	s = tmp;
	p->len = ft_strlen(s);
	if (p->len >= p->widht && !(p->f & (F_POINT)))
	{
		type_hexa_cap_option(p, nb);
		type_hexa_basic_fill(p, s);
		return ;
	}
	else
		type_hexa_mod(p, nb);
	if (p->widht == 0 && p->precision == 1 && nb != 0)
	{
		type_hexa_cap_option(p, nb);
		type_hexa_basic_fill(p, s);
		return ;
	}
	type_hexa_cap_widht(p, s, nb);
}
