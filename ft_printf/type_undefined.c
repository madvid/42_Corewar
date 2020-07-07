/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_undefined.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:47:04 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 12:54:39 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	undefined_spe_fill(t_print *p, int len)
{
	if (p->f & (F_ZERO) && !(p->f & (F_POINT)))
	{
		while (len < p->widht)
		{
			fill_buffer('0', p);
			len++;
		}
	}
	else if (!(p->f & (F_POINT)))
	{
		while (len < p->widht)
		{
			fill_buffer(' ', p);
			len++;
		}
	}
	fill_buffer(p->type, p);
}

static void	undefined_widht(t_print *p)
{
	int len;

	len = 1;
	if (len >= p->widht)
	{
		fill_buffer(p->type, p);
		return ;
	}
	else if (len < p->widht && !(p->f & (F_MINUS)))
		undefined_spe_fill(p, len);
	else if (len < p->widht && p->f & (F_MINUS))
	{
		fill_buffer(p->type, p);
		while (len < p->widht)
		{
			fill_buffer(' ', p);
			len++;
		}
	}
}

void		undefined_type(t_print *p)
{
	undefined_widht(p);
	return ;
}
