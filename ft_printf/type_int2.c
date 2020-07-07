/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_int2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 09:36:17 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/03 11:27:28 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	type_int_size(t_print *p, long long nb)
{
	if (p->f & (F_LONG))
		nb = va_arg(p->ap, long);
	else if (p->f & (F_LONG2))
		nb = va_arg(p->ap, long long);
	else if (p->f & (F_SHORT2))
		nb = (char)va_arg(p->ap, int);
	else if (p->f & (F_INT))
		nb = va_arg(p->ap, intmax_t);
	else if ((p->f & (F_SIZET)) && (p->f & (F_SHORT)))
		nb = va_arg(p->ap, size_t);
	else if (p->f & (F_SIZET))
		nb = va_arg(p->ap, ssize_t);
	else if (p->f & (F_SHORT))
		nb = (short)va_arg(p->ap, int);
	else
		nb = va_arg(p->ap, int);
	return (nb);
}

void		type_int_mod(t_print *p, long long nb)
{
	p->len = (nb == 0 && p->f & (F_POINT)) ? p->len - 1 : p->len;
	p->len = (nb >= 0 && p->f & (F_SPACE) && !(p->f & (F_POINT)))
		? p->len + 1 : p->len;
	p->len = (nb >= 0 && p->f & (F_PLUS) && !(p->f & (F_POINT)))
		? p->len + 1 : p->len;
	p->diff = (!(p->f & (F_POINT))) ? p->widht - p->precision + 1 : p->widht;
	p->diff = (p->precision > p->len) ? p->widht - p->precision
		: p->widht - p->len;
}

void		type_int_mod2(t_print *p, long long nb)
{
	p->diff = (nb >= 0 && p->f & (F_SPACE) && p->precision > 1)
		? p->diff - 1 : p->diff;
	p->diff = (nb >= 0 && p->f & (F_PLUS) && p->precision > 1)
		? p->diff - 1 : p->diff;
	p->diff = (nb > 0 && p->f & (F_PLUS) && p->f & (F_POINT)
			&& p->precision == 1) ? p->diff - 1 : p->diff;
	p->diff = (nb > 0 && p->f & (F_SPACE) && p->f & (F_POINT)
			&& p->precision == 1) ? p->diff - 1 : p->diff;
}

void		type_int_no_idea(t_print *p, char *s, long long nb)
{
	p->len = (nb < 0 && p->precision > 1) ? p->len - 1 : p->len;
	p->diff = (nb < 0 && p->f & (F_SPACE) && p->precision > p->len)
		? p->diff - 1 : p->diff;
	p->diff = (nb < 0 && p->f & (F_PLUS) && p->precision > p->len)
		? p->diff - 1 : p->diff;
	p->diff = (nb < 0 && !(p->f & (F_PLUS)) && !(p->f & (F_SPACE))
			&& p->precision > p->len) ? p->diff - 1 : p->diff;
	while (p->diff > 0)
	{
		fill_buffer(' ', p);
		p->diff--;
	}
	if (nb < 0 && p->precision > 1)
	{
		fill_buffer('-', p);
		++s;
	}
	type_int_option(p, nb);
	type_int_precision(p, s, nb);
}

void		type_int_spe_fill(t_print *p, char *s, long long nb)
{
	if (p->f & (F_ZERO) && (!(p->f & (F_POINT))
		|| (p->f & (F_STAR) && p->f & (F_POINT))))
	{
		if (nb < 0)
		{
			fill_buffer('-', p);
			++s;
		}
		type_int_option(p, nb);
		while (p->diff > 0)
		{
			fill_buffer('0', p);
			p->diff--;
		}
		type_int_precision(p, s, nb);
	}
	else
		type_int_no_idea(p, s, nb);
}
