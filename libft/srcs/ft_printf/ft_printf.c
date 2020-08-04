/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:48:26 by weilin            #+#    #+#             */
/*   Updated: 2020/02/23 16:19:26 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	t_data t;

	ft_bzero(&t, sizeof(t));
	va_start(t.valist, fmt);
	if ((t.fd = 1) && fmt)
	{
		t.len = (int)ft_strlen(fmt);
		while (t.i < t.len)
		{
			if (fmt[t.i] == '%' && t.len == 1)
				break ;
			else if (fmt[t.i] == '%' && fmt[t.i + 1] == '%')
			{
				t.nb_print += write(t.fd, "%", 1);
				t.i += 2;
			}
			else if (fmt[t.i] == '%' && fmt[t.i + 1] != '%')
				parse(fmt, &t);
			else
				t.nb_print += write(t.fd, fmt + (t.i)++, 1);
		}
	}
	va_end(t.valist);
	return (t.nb_print);
}
