/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:15:28 by yaye              #+#    #+#             */
/*   Updated: 2020/09/01 17:31:12 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"
#include "libft.h"

void	parse_c(t_pf *env, t_pfarg *arg)
{
	unsigned short	d;

	if (arg->mod > 3)
		d = va_arg(env->vali, int);
	else
		d = (unsigned char)va_arg(env->vali, int);
	arg->len = 1;
	arg->fill = arg->fld - arg->len + 1;
	if (arg->flg.neg)
	{
		fill_buf(env, d);
		while (--arg->fill > 0)
			fill_buf(env, ' ');
	}
	else
	{
		while (--arg->fill > 0)
			fill_buf(env, ' ');
		fill_buf(env, d);
	}
}

void	parse_percent(t_pf *env, t_pfarg *arg)
{
	arg->extra = (arg->flg.zro) ? '0' : ' ';
	if (arg->flg.neg)
	{
		fill_buf(env, '%');
		while (--arg->fld > 0)
			fill_buf(env, arg->extra);
	}
	else
	{
		while (--arg->fld > 0)
			fill_buf(env, arg->extra);
		fill_buf(env, '%');
	}
}
