/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_ox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:08:09 by weilin            #+#    #+#             */
/*   Updated: 2020/08/04 12:02:08 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

void	fillwidth_base(t_data *t, int n)
{
	int i;

	if (n == 0)
		n = (t->flag.width && !t->flag.prec) ? 0 : 1;
	i = (n) ? (t->flag.width - ft_strlen(t->bf)) : t->flag.width;
	while (i > 0)
	{
		t->nb_print += ((t->flag.zero) == 1 ?
			write(t->fd, "0", 1) : write(t->fd, " ", 1));
		i--;
	}
}

int		base_width(char tp, t_data *t)
{
	char	*tmp;
	char	*new;
	int		len;
	int		i;
	int		x;

	x = (tp == 'x' || tp == 'X') ? 2 : 0;
	len = ft_strlen(t->bf) + x;
	if (t->flag.width > len)
	{
		i = t->flag.width - len;
		if (!(tmp = ft_strnew_c(i, '0')))
			return (0);
		if (!(new = ft_strjoin(tmp, t->bf)))
			return (0);
		free(tmp);
		free(t->bf);
		t->bf = new;
	}
	return (1);
}

int		base_hash(char tp, t_data *t)
{
	char *tmp;

	if (t->flag.width && t->flag.zero == 1)
		if (!base_width(tp, t))
			return (0);
	if (tp == 'o' && t->bf[0] != '0')
	{
		if (!(tmp = ft_strjoin("0", t->bf)))
			return (0);
		free(t->bf);
		t->bf = tmp;
	}
	else if (tp == 'x' || tp == 'X')
	{
		if (!(tmp = ft_strjoin((tp == 'x' ? "0x" : "0X"), t->bf)))
			return (0);
		free(t->bf);
		t->bf = tmp;
	}
	return (1);
}

void	print_base(char type, t_data *t, int n)
{
	if (type != 'o' && (n == 0 || t->bf[0] == '0' || t->bf[0] == '\0'))
		t->flag.hash = 0;
	if (!(addr_precision(t)))
		return ;
	if ((t->flag.hash) && !base_hash(type, t))
		return ;
	if (t->flag.minus != 1)
		fillwidth_base(t, n);
	if (!(t->flag.prec == 0 && n == 0))
		t->nb_print += write(1, t->bf, ft_strlen(t->bf));
	else if ((type == 'o') && n == 0 && t->flag.hash)
		t->nb_print += write(1, t->bf, ft_strlen(t->bf));
	if (t->flag.minus == 1)
		fillwidth_base(t, n);
	free(t->bf);
	t->i++;
}

void	type_base(char type, t_data *t)
{
	unsigned long val;

	(t->flag.minus == 1 || t->flag.prec >= 0) ? t->flag.zero = 0 : 0;
	t->flag.plus = 0;
	t->flag.space = 0;
	init_uint_arg(t, &val);
	if (type == 'X' || type == 'x')
		conv_hexa(t, val);
	else if (type == 'o')
		conv_octal(t, val);
	if (!(t->bf))
		return ;
	if (type == 'x')
		ft_strtolower(t->bf);
	print_base(type, t, (val) ? 1 : 0);
}
