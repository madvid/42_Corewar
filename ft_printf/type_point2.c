/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_point2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:16:34 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 15:29:24 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_point_null(t_print *p)
{
	if (p->f & (F_POINT) && p->precision == 1)
	{
		fill_buffer('0', p);
		fill_buffer('x', p);
	}
	else
	{
		fill_buffer('0', p);
		fill_buffer('x', p);
	}
}

void	type_point_precision(t_print *p, long long addr)
{
	p->len = (addr == 0) ? p->len - 1 : p->len;
	while (p->len < p->precision)
	{
		fill_buffer('0', p);
		p->len++;
	}
}

void	type_bin_spe_fill(t_print *p, char *s, int nb)
{
	if (p->f & (F_ZERO) && !(p->f & (F_POINT)))
	{
		s = type_bin_option(p, nb, s);
		while (p->diff > 0)
		{
			fill_buffer('0', p);
			p->diff--;
		}
		type_bin_precision(p, s, nb);
	}
	else
	{
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
		s = type_bin_option(p, nb, s);
		type_bin_precision(p, s, nb);
	}
}

void	type_bin_mod(t_print *p, int nb)
{
	p->len = (nb == 0 && !(p->f & (F_POINT))) ? p->len - 1 : p->len;
	p->len = (nb == 0 && p->f & (F_POINT)) ? p->len - 1 : p->len;
	p->len = (nb < 0) ? p->len + 3 : p->len;
	p->diff = (!(p->f & (F_POINT))) ? p->widht - p->precision : p->widht;
	p->diff = (p->precision > p->len) ? p->widht - p->precision
		: p->widht - p->len;
}

void	type_str_spe_fill(t_print *p, char *s, int len)
{
	if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& !(p->f & (F_MINUS)))
		type_str_spe_fill2(p, s, len);
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& p->f & (F_MINUS))
	{
		type_str_precision(p, s);
		while (len < p->diff)
		{
			fill_buffer(' ', p);
			len++;
		}
	}
	else
		type_str_precision(p, s);
}
