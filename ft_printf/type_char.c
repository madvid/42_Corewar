/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_char1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 15:00:13 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/04 14:20:54 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	type_char_widht(t_print *p, char c)
{
	int		len;

	len = 0;
	if (p->f & (F_ZERO) && !(p->f & (F_MINUS)))
	{
		while (len < p->widht - 1)
		{
			fill_buffer('0', p);
			len++;
		}
	}
	else
	{
		while (len < p->widht - 1)
		{
			fill_buffer(' ', p);
			len++;
		}
	}
}

void		type_char(t_print *p)
{
	char c;

	c = va_arg(p->ap, int);
	if (p->f & (F_MINUS))
	{
		fill_buffer(c, p);
		type_char_widht(p, c);
	}
	else
	{
		type_char_widht(p, c);
		fill_buffer(c, p);
	}
}
