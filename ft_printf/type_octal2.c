/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_octal2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:55:45 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 17:24:36 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	type_octal_size(t_print *p, unsigned long long addr)
{
	if (p->f & (F_SHORT))
		addr = (unsigned short int)va_arg(p->ap, unsigned int);
	else if (p->f & (F_LONG))
		addr = va_arg(p->ap, unsigned long);
	else if (p->f & (F_LONG2))
		addr = va_arg(p->ap, unsigned long long);
	else if (p->f & (F_SHORT2))
	{
		addr = va_arg(p->ap, unsigned int);
		addr = (unsigned char)addr;
	}
	else if (p->f & (F_INT))
		addr = va_arg(p->ap, intmax_t);
	else
		addr = va_arg(p->ap, unsigned int);
	return (addr);
}

void				type_octal_mod(t_print *p, unsigned long long addr)
{
	p->len = (addr == 0 && !(p->f & (F_POINT))) ? p->len - 1 : p->len;
	p->len = (addr == 0 && p->f & (F_POINT)) ? p->len - 1 : p->len;
	p->len = (p->f & (F_SHARP)) ? p->len + 1 : p->len;
	p->diff = (!(p->f & (F_POINT))) ? p->widht - p->precision : p->widht;
	p->diff = (p->precision > p->len) ? p->widht - p->precision
		: p->widht - p->len;
}

void				typeospefill(t_print *p, char *s, unsigned long long addr)
{
	if (p->f & (F_ZERO) && !(p->f & (F_POINT)))
	{
		type_octal_option(p);
		while (p->diff > 0)
		{
			fill_buffer('0', p);
			p->diff--;
		}
		type_octal_precision(p, s, addr);
	}
	else
	{
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
		type_octal_option(p);
		type_octal_precision(p, s, addr);
	}
}
