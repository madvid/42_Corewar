/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_u2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 11:22:45 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 15:04:34 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	type_u_size(t_print *p, unsigned long long nb)
{
	if (p->type == 'U')
	{
		nb = va_arg(p->ap, unsigned long long);
		return (nb);
	}
	if (p->f & (F_SHORT))
	{
		nb = va_arg(p->ap, int);
		nb = (short unsigned int)nb;
	}
	else if (p->f & (F_LONG))
		nb = va_arg(p->ap, long unsigned int);
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

void				type_u_mod(t_print *p, unsigned long long nb)
{
	p->diff = (!(p->f & (F_POINT))) ? p->widht - p->precision : p->widht;
	p->diff = (p->precision > p->len) ? p->widht - p->precision
		: p->widht - p->len;
	p->len = (nb == 0 && !(p->f & (F_POINT))) ? p->len - 1 : p->len;
}

void				type_u_spe_fill(t_print *p, char *s, unsigned long long nb)
{
	if (p->f & (F_ZERO) && !(p->f & (F_POINT)))
	{
		while (p->diff > 0)
		{
			fill_buffer('0', p);
			p->diff--;
		}
		type_u_precision(p, s, nb);
	}
	else
	{
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
		type_u_precision(p, s, nb);
	}
}
