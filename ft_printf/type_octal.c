/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_octal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 10:28:15 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 17:30:30 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_octal_option(t_print *p)
{
	if (p->f & (F_SHARP))
		fill_buffer('0', p);
}

void	type_octal_precision(t_print *p, char *s, unsigned long long addr)
{
	if (p->len >= p->precision && addr != 0)
	{
		type_hexa_basic_fill(p, s);
		return ;
	}
	if (p->len < p->precision || p->precision == 1)
	{
		while (p->len < p->precision && p->f & (F_POINT) && p->precision != 1)
		{
			fill_buffer('0', p);
			p->len++;
		}
		(addr == 0 && p->f & (F_POINT) && p->widht > 0 && p->precision == 1
			&& !(p->f & (F_SHARP))) ? fill_buffer(' ', p) : 0;
		if (addr != 0 || ((addr == 0) && !(p->f & (F_POINT))
					&& !(p->f & (F_SHARP))))
			type_hexa_basic_fill(p, s);
		return ;
	}
	else
		fill_buffer(' ', p);
}

void	type_octal_widht(t_print *p, char *s, unsigned long long addr)
{
	if ((p->len > p->widht && p->precision == 1 && addr != 0)
			|| (p->len >= p->widht && addr != 0))
	{
		type_octal_option(p);
		type_octal_precision(p, s, addr);
	}
	else if (p->widht <= p->precision)
	{
		type_octal_option(p);
		type_octal_precision(p, s, addr);
	}
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& !(p->f & (F_MINUS)))
		typeospefill(p, s, addr);
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& p->f & (F_MINUS))
	{
		type_octal_option(p);
		type_octal_precision(p, s, addr);
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
	}
}

void	type_octal(t_print *p)
{
	unsigned long long		addr;
	char					*s;
	char					*tmp;

	addr = type_octal_size(p, addr);
	s = ft_itoa_base2(addr, "01234567");
	free_type(tmp, s);
	p->len = ft_strlen(s);
	if (p->len >= p->widht && !(p->f & (F_POINT)))
	{
		type_octal_option(p);
		if (addr == 0 && p->f & (F_SHARP))
			return ;
		type_hexa_basic_fill(p, s);
		return ;
	}
	else
		type_octal_mod(p, addr);
	if (p->widht == 0 && p->precision == 1 && addr != 0)
	{
		type_octal_option(p);
		type_hexa_basic_fill(p, s);
		return ;
	}
	type_octal_widht(p, s, addr);
}
