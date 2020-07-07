/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:45:13 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 15:29:42 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_point_fill(t_print *p, char *dst)
{
	if (dst[0] == 'f')
	{
		fill_buffer('0', p);
		fill_buffer('x', p);
		fill_buffer('7', p);
	}
	else
	{
		fill_buffer('0', p);
		fill_buffer('x', p);
	}
}

void	type_point_widht2(t_print *p)
{
	while (p->len < p->widht && p->f & (F_ZERO))
	{
		fill_buffer('0', p);
		p->len++;
	}
	while (p->len < p->widht)
	{
		fill_buffer(' ', p);
		p->len++;
	}
}

void	type_point_null(t_print *p, long long addr)
{
	if (p->f & (F_MINUS))
	{
		fill_point_null(p);
		if (p->prec != 2)
			fill_buffer('0', p);
		type_point_widht2(p);
	}
	else
	{
		type_point_widht2(p);
		fill_point_null(p);
		if (p->prec != 2)
			fill_buffer('0', p);
	}
	p->len--;
	type_point_precision(p, addr);
}

void	type_point(t_print *p)
{
	char		*dst;
	long long	addr;
	char		*tmp;

	addr = va_arg(p->ap, long long);
	dst = ft_itoa_base2(addr, "0123456789abcdef");
	tmp = dst;
	free(dst);
	dst = tmp;
	p->len = ft_strlen(dst);
	p->len = (dst[0] == 'f') ? p->len + 3 : p->len + 2;
	if (addr == 0)
	{
		type_point_null(p, addr);
		return ;
	}
	if (p->f & (F_MINUS))
	{
		type_point_fill(p, dst);
		type_hexa_basic_fill(p, dst);
		type_point_widht2(p);
	}
	else
		type_point2(p, dst, addr);
}
