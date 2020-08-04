/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_csp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:42:55 by weilin            #+#    #+#             */
/*   Updated: 2020/02/24 16:01:16 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_chars(char type, t_data *t)
{
	unsigned char	ch;
	char			*str;

	t->flag.minus == 1 ? t->flag.zero = 0 : 0;
	if (type == 'c')
	{
		ch = (unsigned char)va_arg(t->valist, int);
		print_char(t, ch);
	}
	else if (type == 's')
	{
		if ((str = (char*)va_arg(t->valist, char*)) != NULL)
		{
			if (!(t->bf = ft_strdup(str)))
				return ;
		}
		else if (!(t->bf = ft_strdup("(null)")))
			return ;
		print_str(t);
	}
}

void	type_percent(t_data *t)
{
	int				tmp;

	tmp = t->flag.width;
	if (t->flag.minus == 1)
	{
		t->nb_print += write(t->fd, "%", 1);
		while (tmp-- > 1)
			t->nb_print += write(t->fd, " ", 1);
	}
	else
	{
		while (tmp-- > 1)
			t->nb_print += (t->flag.zero ?
					write(t->fd, "0", 1) : write(t->fd, " ", 1));
		t->nb_print += write(t->fd, "%", 1);
	}
	t->i++;
}

void	type_addr(t_data *t)
{
	unsigned long	val;

	t->flag.minus == 1 ? t->flag.zero = 0 : 0;
	val = va_arg(t->valist, unsigned long);
	if (t->flag.prec == 0)
		t->bf = ft_strdup("\0");
	else
		t->bf = ft_ultoa_base(val, 16);
	if (!t->bf)
		return ;
	ft_strtolower(t->bf);
	print_addr(t);
}
