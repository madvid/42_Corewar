/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 10:57:44 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/24 14:06:39 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_tab(void)
{
	int n;

	n = 0;
	while (n < 256)
	{
		g_tab[n] = &undefined_type;
		n++;
	}
	g_tab['c'] = &type_char;
	g_tab['s'] = &type_str;
	g_tab['p'] = &type_point;
	g_tab['o'] = &type_octal;
	g_tab['b'] = &type_bin;
	g_tab['u'] = &type_u;
	g_tab['x'] = &type_hexa;
	g_tab['X'] = &type_hexa_cap;
	g_tab['d'] = &type_int;
	g_tab['i'] = &type_int;
	g_tab['U'] = &type_u;
	g_tab['f'] = &type_float;
}

void	init_buffer(void)
{
	int n;

	n = 0;
	while (n < BUFF_SIZE)
	{
		g_buff[n] = '\0';
		n++;
	}
	g_i = 0;
}

void	display_buffer(t_print *p)
{
	p->count += write(1, g_buff, g_i);
	init_buffer();
}

void	fill_buffer(char c, t_print *p)
{
	g_buff[g_i] = c;
	g_i++;
	if (g_i == BUFF_SIZE)
		display_buffer(p);
}
