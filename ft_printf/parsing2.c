/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:11:50 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/09 17:37:02 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parsing_widht2(t_print *p)
{
	char	*stock;
	int		i;

	i = 0;
	stock = ft_strnew(-1);
	while (*p->format >= '0' && *p->format <= '9')
	{
		stock[i] = *p->format;
		i++;
		++p->format;
	}
	stock[i] = '\0';
	p->widht = ft_atoi(stock);
	free(stock);
}

void	parsing_precision2(t_print *p)
{
	p->f |= (F_STAR);
	p->precision = va_arg(p->ap, int);
	p->prec = (p->precision == 0) ? 2 : 1;
	++p->format;
}

void	free_type(char *tmp, char *s)
{
	tmp = s;
	free(s);
	s = tmp;
}
