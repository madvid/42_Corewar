/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 11:04:54 by yaye              #+#    #+#             */
/*   Updated: 2019/07/27 11:04:56 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	to_p(unsigned long u, char *s, t_arg *arg)
{
	char	*base;

	base = "0123456789abcdef";
	if (u < 16)
	{
		arg->len++;
		s[arg->i++] = base[u];
	}
	else
	{
		arg->len++;
		to_p(u / 16, s, arg);
		s[arg->i++] = base[u % 16];
	}
}

void	fill_pneg(char *n, t_pf *env, t_arg *arg)
{
	int		i;

	fill_buf(env, '0');
	fill_buf(env, arg->extra);
	arg->fill = arg->fld - arg->len - 1;
	while (--arg->prc > 0)
		fill_buf(env, '0');
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
	while (--arg->fill > 0)
		fill_buf(env, ' ');
}

void	fill_pels(char *n, t_pf *env, t_arg *arg)
{
	int		i;

	arg->fill = arg->fld - arg->len - 1;
	while (--arg->fill > 0)
		fill_buf(env, ' ');
	fill_buf(env, '0');
	fill_buf(env, arg->extra);
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
}

void	parse_p(t_pf *env, t_arg *arg)
{
	unsigned long	d;
	char			n[21];

	arg->extra = 'x';
	d = va_arg(env->vali, unsigned long);
	ft_bzero(n, 21);
	to_p(d, n, arg);
	if (arg->flg.neg)
		fill_pneg(n, env, arg);
	else
		fill_pels(n, env, arg);
}
