/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_int3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 11:12:40 by armajchr          #+#    #+#             */
/*   Updated: 2019/08/12 11:22:51 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*type_int_spe_fill2(t_print *p, char *s, long long nb)
{
	if (nb < 0)
	{
		fill_buffer('-', p);
		++s;
		p->len--;
	}
	return (s);
}

void		type_int_spe_fill3(t_print *p, char *s, long long nb)
{
	if (nb == -1 && p->precision > 1)
	{
		fill_buffer('-', p);
		++s;
		p->len--;
		p->diff--;
	}
	type_int_option(p, nb);
	type_int_precision(p, s, nb);
	while (p->diff > 0)
	{
		fill_buffer(' ', p);
		p->diff--;
	}
}
