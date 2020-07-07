/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 12:49:55 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 17:37:56 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parsing_flag(t_print *p)
{
	while ((p->n = ft_strchrf("# +0-", *p->format, 0)) > -1 && ++p->format)
		p->f |= (1 << p->n);
	if (p->f & (F_PLUS))
		p->f &= ~(F_SPACE);
	if (p->f & (F_MINUS))
		p->f &= ~(F_ZERO);
}

void	parsing_widht(t_print *p)
{
	if (*p->format == '*' && ft_isdigit(p->format[1]) == 1)
	{
		p->trash = va_arg(p->ap, int);
		++p->format;
	}
	if (*p->format == '*')
	{
		p->widht = va_arg(p->ap, int);
		(p->widht < 0) ? p->f |= (F_MINUS) : 0;
		p->widht = (p->widht < 0) ? -p->widht : p->widht;
		++p->format;
		return ;
	}
	if (*p->format >= '0' && *p->format <= '9')
		parsing_widht2(p);
}

void	parsing_precision(t_print *p, int i)
{
	char	*stock;

	if (*p->format == '.')
	{
		p->f |= (F_POINT);
		++p->format;
		if (*p->format == '*')
		{
			parsing_precision2(p);
			return ;
		}
		stock = ft_strnew(-1);
		while (*p->format >= '0' && *p->format <= '9')
		{
			stock[i] = *p->format;
			i++;
			++p->format;
		}
		stock[i] = '\0';
		p->precision = ft_atoi(stock);
		p->prec = (p->precision == 0) ? 2 : 1;
		free(stock);
	}
	p->precision = (p->precision == 0) ? 1 : p->precision;
}

void	parsing_size(t_print *p)
{
	while (*p->format == 'j' || *p->format == 'z' || *p->format == 'h'
			|| *p->format == 'l' || *p->format == 'L')
	{
		if (*p->format == 'j')
			p->f |= (F_INT);
		else if (*p->format == 'z')
			p->f |= (F_SIZET);
		else if (*p->format == 'L')
			p->f |= (F_FLOAT);
		else if (*p->format == 'l')
			p->f |= (p->format[1] == 'l' && ++p->format) ? F_LONG2 : F_LONG;
		else if (*p->format == 'h')
			p->f |= (p->format[1] == 'h' && ++p->format) ? F_SHORT2 : F_SHORT;
		else
			break ;
		++p->format;
	}
}

void	parsing_type(t_print *p)
{
	if (*p->format == 'c' || *p->format == 'd' || *p->format == 'i'
			|| *p->format == 'p' || *p->format == 'o' || *p->format == 'u'
			|| *p->format == 'x' || *p->format == 'X' || *p->format == 'f'
			|| *p->format == 's' || *p->format == 'b' || *p->format == 'U')
		p->type = *p->format;
	else
		p->type = *p->format;
}
