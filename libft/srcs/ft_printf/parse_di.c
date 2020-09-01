/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 11:29:01 by yaye              #+#    #+#             */
/*   Updated: 2020/09/01 17:31:28 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"
#include "libft.h"

void	to_di(intmax_t n, char *s, t_pfarg *arg)
{
	uintmax_t	u;

	if (n < 0)
	{
		arg->extra = '-';
		u = -n;
	}
	else
		u = n;
	if (u < 10)
	{
		arg->len++;
		s[arg->i++] = u + '0';
	}
	else
	{
		arg->len++;
		to_di(u / 10, s, arg);
		s[arg->i++] = u % 10 + '0';
	}
}

void	fill_dineg(char *n, t_pf *env, t_pfarg *arg)
{
	int		i;

	if (arg->prc >= 0 && n[0] == '0')
		arg->len = 0;
	arg->prc = (arg->prc < arg->len) ? 0 : arg->prc - arg->len;
	if (arg->extra)
	{
		fill_buf(env, arg->extra);
		arg->fill = arg->fld - (arg->prc++ + arg->len);
	}
	else
		arg->fill = arg->fld - (arg->prc++ + arg->len) + 1;
	while (--arg->prc > 0)
		fill_buf(env, '0');
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
	while (--arg->fill > 0)
		fill_buf(env, ' ');
}

void	fill_dizro(char *n, t_pf *env, t_pfarg *arg)
{
	int		i;

	if (arg->extra)
	{
		fill_buf(env, arg->extra);
		arg->fill = arg->fld - arg->len;
	}
	else
		arg->fill = arg->fld - arg->len + 1;
	while (--arg->fill > 0)
		fill_buf(env, '0');
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
}

void	fill_diels(char *n, t_pf *env, t_pfarg *arg)
{
	int		i;

	if (arg->prc >= 0 && n[0] == '0')
		arg->len = 0;
	arg->prc = (arg->prc < arg->len) ? 0 : arg->prc - arg->len;
	arg->fill = (arg->extra) ? arg->fld - (arg->prc++ + arg->len) \
		: arg->fld - (arg->prc++ + arg->len) + 1;
	while (--arg->fill > 0)
		fill_buf(env, ' ');
	if (arg->extra)
		fill_buf(env, arg->extra);
	while (--arg->prc > 0)
		fill_buf(env, '0');
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
}

void	parse_di(t_pf *env, t_pfarg *arg)
{
	intmax_t		d;
	char			n[21];

	arg->extra = (arg->flg.pls) ? arg->flg.pls : arg->flg.spc;
	if (arg->prc >= 0)
		arg->flg.zro = 0;
	if (arg->mod >= 3)
		d = (long)va_arg(env->vali, intmax_t);
	else if (arg->mod == 2)
		d = (short)va_arg(env->vali, intmax_t);
	else if (arg->mod == 1)
		d = (char)va_arg(env->vali, intmax_t);
	else
		d = va_arg(env->vali, int);
	ft_bzero(n, 21);
	to_di(d, n, arg);
	if (arg->flg.neg)
		fill_dineg(n, env, arg);
	else if (arg->flg.zro)
		fill_dizro(n, env, arg);
	else
		fill_diels(n, env, arg);
}
