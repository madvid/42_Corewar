/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:55:42 by weilin            #+#    #+#             */
/*   Updated: 2020/02/26 11:24:46 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_width(t_data *t)
{
	t->flag.width = va_arg(t->valist, int);
	if (t->flag.width < 0)
	{
		t->flag.width = -(t->flag.width);
		t->flag.minus = 1;
	}
}

void	parse_mod(const char *fmt, t_data *t)
{
	if (fmt[t->i] == 'l' && fmt[t->i + 1] != 'l' && t->mod == MOD_n)
		t->mod = MOD_l;
	else if (fmt[t->i] == 'l' && fmt[t->i + 1] == 'l')
		t->mod = MOD_ll;
	else if (fmt[t->i] == 'h' && fmt[t->i + 1] != 'h' && t->mod == MOD_n)
		t->mod = MOD_h;
	else if (fmt[t->i] == 'h' && fmt[t->i + 1] == 'h')
		t->mod = MOD_hh;
	else if (fmt[t->i] == 'j')
		t->mod = MOD_j;
	else if (fmt[t->i] == 'z')
		t->mod = MOD_z;
}

void	parse_prec(const char *fmt, t_data *t)
{
	if (t->flag.prec >= 0)
	{
		t->i++;
		return ;
	}
	else if (fmt[t->i] == '.' && fmt[t->i + 1] == '*')
	{
		t->flag.prec = va_arg(t->valist, int);
		t->i += 2;
	}
	else if (fmt[t->i] == '.' && ft_isdigit(fmt[t->i + 1]))
	{
		t->i++;
		t->flag.prec = ft_atoi(fmt + t->i);
		while (ft_isdigit(fmt[t->i]))
			t->i++;
	}
	else
		t->flag.prec = 0;
}
