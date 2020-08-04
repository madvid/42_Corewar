/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:54:00 by weilin            #+#    #+#             */
/*   Updated: 2020/02/26 11:45:55 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_type(const char *fmt, t_data *t)
{
	if (fmt[t->i] == 'c' || fmt[t->i] == 's')
		type_chars(fmt[t->i], t);
	else if (fmt[t->i] == '%')
		type_percent(t);
	else if (fmt[t->i] == 'p')
		type_addr(t);
	else if (fmt[t->i] == 'd' || fmt[t->i] == 'i')
		type_int(t);
	else if (fmt[t->i] == 'u')
		type_uint(t);
	else if (fmt[t->i] == 'o' || fmt[t->i] == 'x' || fmt[t->i] == 'X')
		type_base(fmt[t->i], t);
	else if (fmt[t->i] != '\0')
		print_char(t, fmt[t->i]);
}

void	parse_flag(const char *fmt, t_data *t)
{
	while (ft_strchr("'+-0# *.123456789hlLjz", fmt[t->i]))
	{
		fmt[t->i] == '+' ? t->flag.plus = 1 : 0;
		fmt[t->i] == '-' ? t->flag.minus = 1 : 0;
		fmt[t->i] == '0' ? t->flag.zero = 1 : 0;
		fmt[t->i] == '#' ? t->flag.hash = 1 : 0;
		fmt[t->i] == ' ' ? t->flag.space = 1 : 0;
		fmt[t->i] == '*' ? parse_width(t) : 0;
		fmt[t->i] >= 'L' && fmt[t->i] <= 'z' ? parse_mod(fmt, t) : 0;
		if (fmt[t->i] == '.')
			parse_prec(fmt, t);
		else if (ft_isdigit(fmt[t->i]))
		{
			t->flag.width = ft_atoi(fmt + t->i);
			while (ft_isdigit(fmt[t->i]))
				t->i++;
		}
		else
			t->i++;
	}
}

void	parse(const char *fmt, t_data *t)
{
	t->i++;
	init_flag(t);
	parse_flag(fmt, t);
	if (t->i > (int)ft_strlen(fmt) - 1)
		return ;
	parse_type(fmt, t);
}
