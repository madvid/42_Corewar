/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_point3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 11:29:35 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 15:20:44 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_str_spe_fill2(t_print *p, char *s, int len)
{
	if (p->f & (F_ZERO))
	{
		while (len < p->diff)
		{
			fill_buffer('0', p);
			len++;
		}
		type_str_precision(p, s);
		return ;
	}
	while (len < p->diff)
	{
		fill_buffer(' ', p);
		len++;
	}
	type_str_precision(p, s);
}

void	type_point2(t_print *p, char *dst, long long addr)
{
	if (p->widht > p->len && addr != 0)
	{
		type_point_widht2(p);
		type_point_fill(p, dst);
	}
	else if (addr != 0)
	{
		type_point_fill(p, dst);
		type_point_widht2(p);
	}
	p->len = (dst[0] == 'f') ? p->len - 3 : p->len - 2;
	type_point_precision(p, addr);
	while (*dst && p->prec != 2)
	{
		fill_buffer(*dst, p);
		++dst;
	}
}
