/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 12:49:28 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/16 13:36:09 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_selection(t_print *p)
{
	return ((g_tab[(int)p->type])(p));
}

void	parsing(t_print *p)
{
	parsing_flag(p);
	parsing_widht(p);
	parsing_precision(p, 0);
	parsing_size(p);
	p->widht = (p->widht < 0) ? -p->widht : p->widht;
	p->precision = (p->precision < 0) ? 1 : p->precision;
	parsing_type(p);
	p->precision = (p->precision == 1 && p->type == 'f') ? 6 : p->precision;
	type_selection(p);
	p->f &= ~((F_SHARP) | (F_SPACE) | (F_PLUS) | (F_ZERO) | (F_MINUS)
			| (F_POINT) | (F_SHORT) | (F_SHORT2) | (F_LONG) | (F_LONG2));
	p->precision = 0;
	p->type = 0;
	p->widht = 0;
	p->prec = 0;
	p->len = 0;
	p->diff = 0;
	p->check = 0;
}

int		ft_printf(const char *restrict format, ...)
{
	t_print		p;

	ft_bzero(&p, sizeof(p));
	p.format = (char*)format;
	init_buffer();
	init_tab();
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			++p.format;
			if (!*p.format)
				break ;
			parsing(&p);
		}
		else
			fill_buffer(*p.format, &p);
		++p.format;
	}
	display_buffer(&p);
	va_end(p.ap);
	return (p.count);
}
