/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 12:03:26 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 12:53:12 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_str_precision(t_print *p, char *s)
{
	int len;

	len = -1;
	if (p->len < p->precision || p->precision == 1)
	{
		if (p->prec == 2)
		{
			while (p->len < p->widht)
			{
				fill_buffer(' ', p);
				p->len++;
			}
			return ;
		}
		type_hexa_basic_fill(p, s);
		return ;
	}
	if (p->len > p->precision && p->precision != 1)
	{
		while (++len < p->precision)
		{
			fill_buffer(*s, p);
			++s;
		}
	}
}

void	type_str_widht(t_print *p, char *s)
{
	int len;

	len = 0;
	if (p->len > p->widht && p->precision == 1)
	{
		type_hexa_basic_fill(p, s);
		return ;
	}
	else if (p->widht == 0)
		type_str_precision(p, s);
	else
		type_str_spe_fill(p, s, len);
}

void	type_str(t_print *p)
{
	char	*s;

	s = va_arg(p->ap, char *);
	if (s == NULL)
	{
		s = "(null)";
		p->len = 6;
	}
	else
		p->len = ft_strlen(s);
	if (p->precision < p->len && p->precision != 1)
		p->diff = p->widht - p->precision;
	else if (p->len >= p->widht && !(p->f & (F_POINT)))
	{
		type_hexa_basic_fill(p, s);
		return ;
	}
	else
		p->diff = p->widht - p->len;
	if (p->widht == 0 && p->precision == 1)
	{
		type_hexa_basic_fill(p, s);
		return ;
	}
	type_str_widht(p, s);
}
