/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 11:25:11 by yaye              #+#    #+#             */
/*   Updated: 2019/07/27 11:25:12 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	to_f(long double n, char *s, t_pfarg *arg)
{
	if (naninf(n, s, arg))
		return ;
	if ((!arg->prc && !((unsigned long)n % 2) && n - (unsigned long)n > 0.5) \
		|| (!arg->prc && (unsigned long)n % 2 && n - (unsigned long)n >= 0.5))
		n = n + 1;
	to_u(n, s, arg);
	if (arg->flg.hsh || arg->prc > 0)
	{
		s[arg->i++] = '.';
		arg->len++;
	}
	if (!arg->prc)
		return ;
	while (--arg->prc > 0)
		to_u(n = (n - (unsigned long)n) * 10, s, arg);
	n = (n - (unsigned long)n) * 10;
	if ((!((unsigned long)n % 2) && (n - (unsigned long)n) > 0.5) \
		|| ((unsigned long)n % 2 && (n - (unsigned long)n) >= 0.5))
		n = n + 1;
	to_u(n, s, arg);
}

void	fill_fneg(char *n, t_pf *env, t_pfarg *arg)
{
	int		i;

	if (arg->extra)
	{
		fill_buf(env, arg->extra);
		arg->fill = arg->fld - arg->len;
	}
	else
		arg->fill = arg->fld - arg->len + 1;
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
	while (--arg->fill > 0)
		fill_buf(env, ' ');
}

void	fill_fzro(char *n, t_pf *env, t_pfarg *arg)
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

void	fill_fels(char *n, t_pf *env, t_pfarg *arg)
{
	int		i;

	arg->fill = (arg->extra) ? arg->fld - arg->len : arg->fld - arg->len + 1;
	while (--arg->fill > 0)
		fill_buf(env, ' ');
	if (arg->extra)
		fill_buf(env, arg->extra);
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
}

void	parse_f(t_pf *env, t_pfarg *arg)
{
	long double		d;
	char			n[5000];
	char			*p;

	arg->extra = (arg->flg.pls) ? arg->flg.pls : arg->flg.spc;
	if (arg->prc < 0)
		arg->prc = 6;
	if (arg->mod == 3)
		d = va_arg(env->vali, long double);
	else
		d = va_arg(env->vali, double);
	ft_bzero(n, 5000);
	p = (char *)&d + 9;
	if (*p >> 7 & 1)
	{
		arg->extra = '-';
		d = -d;
	}
	to_f(d, n, arg);
	if (arg->flg.neg)
		fill_fneg(n, env, arg);
	else if (arg->flg.zro)
		fill_fzro(n, env, arg);
	else
		fill_fels(n, env, arg);
}
