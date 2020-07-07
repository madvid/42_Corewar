/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_hexa_cap2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 12:38:32 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/03 13:09:15 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	type_hexa_cap_size(t_print *p, long long nb)
{
	if (p->f & (F_SHORT))
	{
		nb = (unsigned short int)va_arg(p->ap, unsigned int);
	}
	else if (p->f & (F_LONG))
		nb = va_arg(p->ap, unsigned long int);
	else if (p->f & (F_LONG2))
		nb = va_arg(p->ap, unsigned long long int);
	else if (p->f & (F_SHORT2))
	{
		nb = va_arg(p->ap, unsigned int);
		nb = (unsigned char)nb;
	}
	else if (p->f & (F_INT))
		nb = va_arg(p->ap, intmax_t);
	else
		nb = va_arg(p->ap, unsigned int);
	return (nb);
}

void		type_hexa_mod(t_print *p, long long nb)
{
	p->diff = (!(p->f & (F_POINT))) ? p->widht - p->precision : p->widht;
	p->diff = (p->precision > p->len) ? p->widht - p->precision :
		p->widht - p->len;
	p->len = (nb == 0 && !(p->f & (F_POINT))) ? p->len - 1 : p->len;
	p->diff = (nb != 0 && p->f & (F_SHARP)) ? p->diff - 2 : p->diff;
}

void		type_hexa_basic_fill(t_print *p, char *s)
{
	while (*s)
	{
		fill_buffer(*s, p);
		++s;
	}
}

void		type_hexa_cap_spefill2(t_print *p, char *s, long long nb)
{
	type_hexa_cap_option(p, nb);
	type_hexa_cap_precision(p, s, nb);
	while (p->diff > 0)
	{
		fill_buffer(' ', p);
		p->diff--;
	}
}

void		type_hexa_special_fill(t_print *p, char *s, long long nb)
{
	if (p->f & (F_ZERO) && !(p->f & (F_POINT)))
	{
		type_hexa_cap_option(p, nb);
		while (p->diff > 0)
		{
			fill_buffer('0', p);
			p->diff--;
		}
		type_hexa_cap_precision(p, s, nb);
	}
	else
	{
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
		type_hexa_cap_option(p, nb);
		type_hexa_cap_precision(p, s, nb);
	}
}
