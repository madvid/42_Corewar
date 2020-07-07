/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:35:30 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 15:02:52 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_u_precision(t_print *p, char *s, unsigned long long nb)
{
	if (p->len >= p->precision && nb != 0)
	{
		type_hexa_basic_fill(p, s);
		return ;
	}
	if (p->len < p->precision || p->precision == 1)
	{
		(nb == 0 && p->precision > 1 && p->widht >= 0) ? p->len-- : 0;
		while (p->len < p->precision && p->f & (F_POINT) && p->precision != 1)
		{
			fill_buffer('0', p);
			p->len++;
		}
		(nb == 0 && p->f & (F_POINT) && p->widht > 0 && p->precision == 1)
			? fill_buffer(' ', p) : 0;
		if (nb != 0 || ((nb == 0) && !(p->f & (F_POINT))))
			type_hexa_basic_fill(p, s);
		return ;
	}
	else
		fill_buffer(' ', p);
}

void	type_u_widht(t_print *p, char *s, unsigned long long nb)
{
	if (p->len > p->widht && p->precision == 1 && nb != 0)
	{
		type_hexa_basic_fill(p, s);
		return ;
	}
	if (p->widht <= p->precision)
		type_u_precision(p, s, nb);
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& !(p->f & (F_MINUS)))
		type_u_spe_fill(p, s, nb);
	else if (((p->len < p->widht) || (p->diff > 0 && p->precision > 1))
			&& p->f & (F_MINUS))
	{
		type_u_precision(p, s, nb);
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
	}
	else
		type_u_precision(p, s, nb);
}

void	type_u(t_print *p)
{
	unsigned long long	nb;
	char				*s;
	char				*tmp;

	nb = type_u_size(p, nb);
	s = ft_unsigned_itoa(nb);
	tmp = s;
	free(s);
	s = tmp;
	p->len = ft_strlen(s);
	if (p->len >= p->widht && !(p->f & (F_POINT)))
	{
		type_hexa_basic_fill(p, s);
		return ;
	}
	else
		type_u_mod(p, nb);
	if (p->widht == 0 && p->precision == 1 && nb != 0)
	{
		type_hexa_basic_fill(p, s);
		return ;
	}
	type_u_widht(p, s, nb);
}
