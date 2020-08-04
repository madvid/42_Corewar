/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_addr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:40:43 by weilin            #+#    #+#             */
/*   Updated: 2020/02/24 15:59:23 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fillwidth_addr(t_data *t)
{
	int len;
	int i;

	len = ft_strlen(t->bf) + 2;
	i = t->flag.width - len;
	while (i > 0)
	{
		t->nb_print += write(t->fd, " ", 1);
		i--;
	}
}

void	print_hash(char type, t_data *t)
{
	if (type == 'o' && t->bf[0] != '0')
		t->nb_print += write(t->fd, "0", 1);
	else if (type == 'x' || type == 'X')
		t->nb_print += write(t->fd, type == 'x' ? "0x" : "0X", 2);
}

int		addr_precision(t_data *t)
{
	char	*tmp;
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(t->bf);
	if (t->flag.prec > len)
	{
		i = t->flag.prec - len;
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

void	print_addr(t_data *t)
{
	if (!(addr_precision(t)))
		return ;
	if (t->flag.minus == 1)
	{
		print_hash('x', t);
		t->nb_print += write(t->fd, t->bf, ft_strlen(t->bf));
		fillwidth_addr(t);
	}
	else
	{
		fillwidth_addr(t);
		print_hash('x', t);
		t->nb_print += write(t->fd, t->bf, ft_strlen(t->bf));
	}
	free(t->bf);
	t->i++;
}
