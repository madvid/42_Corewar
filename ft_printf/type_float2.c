/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_float2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 10:47:53 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/16 11:47:17 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

float	type_float_size(t_print *p, double nb)
{
	if (p->f & (F_FLOAT))
		nb = va_arg(p->ap, long double);
	else
		nb = (float)va_arg(p->ap, double);
	return (nb);
}

void	type_float_option2(t_print *p, int len, int sign)
{
	p->diff = (p->prec == 2) ? p->widht - len + 1
		: p->widht - len - p->precision;
	p->diff -= (p->f & (F_PLUS)) ? 1 : 0;
	if (p->f & (F_PLUS))
		fill_buffer('+', p);
	if (sign == 1)
	{
		fill_buffer('-', p);
		p->check = 1;
	}
	while (p->diff > 0)
	{
		fill_buffer('0', p);
		p->diff--;
	}
	return ;
}

void	type_nan_widht(t_print *p, char *s)
{
	if (p->f & (F_MINUS))
	{
		type_hexa_basic_fill(p, s);
		p->diff = p->widht - 3;
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
	}
	else
	{
		p->diff = p->widht - 3;
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
		type_hexa_basic_fill(p, s);
	}
}

void	type_inf_widht2(t_print *p, char *s, int len)
{
	p->diff = p->widht - len;
	if (p->f & (F_PLUS))
	{
		fill_buffer('+', p);
		p->diff--;
	}
	type_hexa_basic_fill(p, s);
	while (p->diff > 0)
	{
		fill_buffer(' ', p);
		p->diff--;
	}
}

void	type_inf_widht(t_print *p, char *s, int len)
{
	if (p->f & (F_SPACE))
	{
		fill_buffer(' ', p);
		len++;
	}
	if (!(p->f & (F_MINUS)))
	{
		p->diff = p->widht - len;
		if (p->f & (F_PLUS))
			p->diff--;
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
		if (p->f & (F_PLUS))
			fill_buffer('+', p);
		type_hexa_basic_fill(p, s);
	}
	else if (p->f & (F_MINUS))
		type_inf_widht2(p, s, len);
}
