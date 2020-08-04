/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_uint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:35:11 by mdavid            #+#    #+#             */
/*   Updated: 2020/02/26 08:23:27 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FUNCTION: type_uint
** PARAMTERS: t_data *t: main struct of data.
** DESCRIPTION:
** 	Treat the unsigned int conversion, proccessing flags before calling function
** 	print_int.
** RETURN:
** 	None
*/

void	type_uint(t_data *t)
{
	unsigned long int		n;
	int						neg;
	char					*val;

	(t->flag.prec >= 0) ? t->flag.zero = 0 : 0;
	neg = 0;
	t->flag.plus = 0;
	t->flag.space = 0;
	init_uint_arg(t, &n);
	val = ft_ulltoa(n);
	if (ft_prec_for_int(t, &val) == (int)STAT_ERR ||
		ft_width_for_int(t, &val, ft_strlen(val), neg) == (int)STAT_ERR)
	{
		(val) ? ft_strdel(&val) : 0;
		return ;
	}
	if (!(val))
		return ;
	t->bf = val;
	print_int(t);
}
