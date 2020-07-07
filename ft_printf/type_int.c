/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 12:31:20 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 17:31:22 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		type_int_option(t_print *p, long long nb)
{
	if (p->f & (F_PLUS) && nb >= 0)
		fill_buffer('+', p);
	if (p->f & (F_SPACE) && nb >= 0)
		fill_buffer(' ', p);
}

void		type_int_precision(t_print *p, char *s, long long nb)
{
	if (p->len >= p->precision && nb != 0)
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
		(nb == 0 && p->f & (F_POINT) && p->widht > 0 && p->precision == 1
			&& !(p->f & (F_PLUS)) && !(p->f & (F_SPACE)))
			? fill_buffer(' ', p) : 0;
		if (nb != 0 || ((nb == 0) && !(p->f & (F_POINT))))
			type_hexa_basic_fill(p, s);
		return ;
	}
}

static void	type_int_widht(t_print *p, char *s, long long nb)
{
	if ((p->len > p->widht && p->precision == 1 && nb != 0)
			|| (p->len >= p->widht && nb != 0))
	{
		s = type_int_spe_fill2(p, s, nb);
		type_int_option(p, nb);
		type_int_precision(p, s, nb);
	}
	else if (p->widht <= p->precision)
	{
		if (nb < 0)
		{
			fill_buffer('-', p);
			p->len--;
			++s;
		}
		type_int_option(p, nb);
		type_int_precision(p, s, nb);
	}
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& !(p->f & (F_MINUS)))
		type_int_spe_fill(p, s, nb);
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& p->f & (F_MINUS))
		type_int_spe_fill3(p, s, nb);
}

void		type_int(t_print *p)
{
	long long	nb;
	char		*s;
	char		*tmp;

	nb = type_int_size(p, nb);
	s = ft_itoa(nb);
	free_type(tmp, s);
	p->len = ft_strlen(s);
	if (p->len >= p->widht && !(p->f & (F_POINT)))
	{
		type_int_option(p, nb);
		type_hexa_basic_fill(p, s);
		return ;
	}
	else
		type_int_mod(p, nb);
	type_int_mod2(p, nb);
	if (p->widht == 0 && p->precision == 1 && nb != 0)
	{
		type_int_option(p, nb);
		type_hexa_basic_fill(p, s);
		return ;
	}
	type_int_widht(p, s, nb);
}
