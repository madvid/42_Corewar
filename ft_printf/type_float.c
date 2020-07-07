/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 16:15:48 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/16 13:35:33 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_float_spe_fill(t_print *p, char *s)
{
	while (*s)
	{
		if (*s == '.')
		{
			if (p->prec == 2 && !(p->f & (F_SHARP)))
				return ;
			fill_buffer('.', p);
			++s;
			if (p->prec == 2 && p->f & (F_SHARP))
				return ;
			while (p->diff > 0 && *s)
			{
				fill_buffer(*s, p);
				p->diff--;
				++s;
			}
			return ;
		}
		else
		{
			fill_buffer(*s, p);
			++s;
		}
	}
}

void	type_float_fill(t_print *p, char *s)
{
	if (p->precision < 6 && p->widht == 0 && p->prec == 0)
		p->diff = p->len;
	else
		p->diff = p->precision;
	if (p->check == 1)
		++s;
	type_float_spe_fill(p, s);
}

void	type_float_option(t_print *p, int len, char *s, int sign)
{
	if (p->f & (F_SPACE))
	{
		fill_buffer(' ', p);
		len++;
	}
	if (p->widht > p->precision + p->len && !(p->f & (F_MINUS))
			&& !(p->f & (F_ZERO)))
	{
		p->diff = (p->prec == 2) ? p->widht - len + 1
			: p->widht - len - p->precision;
		p->diff -= (p->f & (F_PLUS)) ? 1 : 0;
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
		if (p->f & (F_PLUS))
			fill_buffer('+', p);
		return ;
	}
	else if (p->widht > p->precision + p->len && p->f & (F_ZERO))
		type_float_option2(p, len, sign);
	else if (p->f & (F_PLUS))
		fill_buffer('+', p);
}

void	type_float_precision(t_print *p, char *s, int len)
{
	if (p->prec == 1 && p->precision <= 6)
		p->diff = p->precision - p->len;
	else if (p->prec == 0)
		p->diff = 6 - p->len;
	else if (p->prec == 2)
		return ;
	else
		p->diff = p->precision - p->len;
	while (p->diff > 0)
	{
		fill_buffer('0', p);
		p->diff--;
	}
	if (p->f & (F_MINUS) && p->widht > p->precision + p->len)
	{
		p->diff = (p->prec == 2) ? p->widht - len + 1
			: p->widht - len - p->precision;
		while (p->diff > 0)
		{
			fill_buffer(' ', p);
			p->diff--;
		}
	}
}

void	type_float(t_print *p)
{
	double	nb;
	char	*s;
	int		sign;
	int		len;
	int		i;

	nb = (float)type_float_size(p, nb);
	sign = get_float_sign(nb, p, i, sign);
	(sign == 1) ? p->f &= ~((F_PLUS) | (F_SPACE)) : 0;
	if (isnan(nb))
	{
		type_nan(p, s);
		return ;
	}
	else if (!isfinite(nb))
	{
		type_inf(p, s, sign, len);
		return ;
	}
	else
	{
		s = ft_itoa_float(nb, p, sign);
		p->precision = (p->prec == 0) ? 6 - p->len : p->precision;
		type_float2(p, nb, sign, s);
	}
}
