/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:13:59 by weilin            #+#    #+#             */
/*   Updated: 2020/02/26 11:15:20 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_flag(t_data *t)
{
	t->flag.plus = 0;
	t->flag.minus = 0;
	t->flag.zero = 0;
	t->flag.space = 0;
	t->flag.hash = 0;
	t->flag.width = 0;
	t->flag.prec = -1;
	t->mod = MOD_n;
}

void	init_int_arg(t_data *t, long int *val)
{
	if (t->mod == MOD_n)
		*val = (long int)va_arg(t->valist, int);
	else if (t->mod == MOD_hh)
		*val = (char)va_arg(t->valist, int);
	else if (t->mod == MOD_h)
		*val = (short int)va_arg(t->valist, int);
	else if (t->mod == MOD_l)
		*val = (long int)va_arg(t->valist, long int);
	else if (t->mod == MOD_ll)
		*val = (long long int)va_arg(t->valist, long long int);
	else if (t->mod == MOD_j)
		*val = (intmax_t)va_arg(t->valist, intmax_t);
	else if (t->mod == MOD_z)
		*val = (size_t)va_arg(t->valist, size_t);
}

void	init_uint_arg(t_data *t, unsigned long *val)
{
	if (t->mod == MOD_n)
		*val = (unsigned long)va_arg(t->valist, unsigned int);
	else if (t->mod == MOD_hh)
		*val = (unsigned char)va_arg(t->valist, unsigned int);
	else if (t->mod == MOD_h)
		*val = (short unsigned int)va_arg(t->valist, unsigned int);
	else if (t->mod == MOD_l)
		*val = (unsigned long)va_arg(t->valist, unsigned long int);
	else if (t->mod == MOD_ll)
		*val = (unsigned long long int)va_arg(t->valist,
			unsigned long long int);
	else if (t->mod == MOD_j)
		*val = (intmax_t)va_arg(t->valist, intmax_t);
	else if (t->mod == MOD_z)
		*val = (size_t)va_arg(t->valist, size_t);
}

void	conv_octal(t_data *t, unsigned long val)
{
	if (t->mod == MOD_n)
		t->bf = ft_uitoa_base((unsigned int)val, 8);
	else if (t->mod == MOD_hh)
		t->bf = ft_uitoa_base((unsigned char)val, 8);
	else if (t->mod == MOD_h)
		t->bf = ft_uitoa_base((unsigned short int)val, 8);
	else if (t->mod == MOD_l)
		t->bf = ft_ultoa_base((unsigned long)val, 8);
	else if (t->mod == MOD_ll)
		t->bf = ft_ulltoa_base((unsigned long long)val, 8);
	else if (t->mod == MOD_j)
		t->bf = ft_ulltoa_base((intmax_t)val, 8);
	else if (t->mod == MOD_z)
		t->bf = ft_ulltoa_base((size_t)val, 8);
}

void	conv_hexa(t_data *t, unsigned long val)
{
	if (t->mod == MOD_n)
		t->bf = ft_uitoa_base((unsigned int)val, 16);
	else if (t->mod == MOD_hh)
		t->bf = ft_uitoa_base((unsigned char)val, 16);
	else if (t->mod == MOD_h)
		t->bf = ft_uitoa_base((unsigned short int)val, 16);
	else if (t->mod == MOD_l)
		t->bf = ft_ultoa_base((unsigned long)val, 16);
	else if (t->mod == MOD_ll)
		t->bf = ft_ulltoa_base((unsigned long long)val, 16);
	else if (t->mod == MOD_j)
		t->bf = ft_ulltoa_base((intmax_t)val, 16);
	else if (t->mod == MOD_z)
		t->bf = ft_ulltoa_base((size_t)val, 16);
}
