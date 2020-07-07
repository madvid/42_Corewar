/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_float3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 11:06:07 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/16 13:35:59 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_nan(t_print *p, char *s)
{
	s = "nan";
	type_nan_widht(p, s);
}

void	type_inf(t_print *p, char *s, int sign, int len)
{
	s = (sign == 1) ? "-inf" : "inf";
	len = (sign == 1) ? 4 : 3;
	type_inf_widht(p, s, len);
}

void	type_float2(t_print *p, double nb, int sign, char *s)
{
	int len;

	len = ft_floatlen(s);
	type_float_option(p, len, s, sign);
	type_float_fill(p, s);
	type_float_precision(p, s, len);
}
